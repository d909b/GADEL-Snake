/**
 *  CellGrid.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "Grid.h"
#include <algorithm>
#include <cmath>
#include <set>

Grid::Grid(uint32_t width, uint32_t height) :
    m_width(width),
    m_height(height)
{
    /** Reserve memory for the grid. */
    m_collisionGrid = new std::set<Actor*>*[m_width];
    
    for(uint32_t i = 0; i < m_width; ++i)
    {
        m_collisionGrid[i] = new std::set<Actor*>[m_height];
    }
}

Grid::~Grid()
{
    /** Free allocated memory. */
    for(uint32_t i = 0; i < m_width; ++i)
    {
        delete[] m_collisionGrid[i];
    }
    
    delete[] m_collisionGrid;
}

void
Grid::LoadBackground(int layer)
{
    for(int i = 0; i < m_width; ++i)
    {
        for(int j = 0; j < m_height; ++j)
        {
            const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
            const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
            
            Actor* groundcell = Actor::Create("ground");
            
            groundcell->SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
            
            /** SetPosition sets the center of the sprite, thus we have to add half the width/height. */
            Vector2 pos = GridToWorldSpace(Vector2(i, j)) + groundcell->GetSize() / 2;;
            groundcell->SetPosition(pos);
        
            theWorld.Add(groundcell, layer);
            
            if(i == m_width - 1 || j == m_height - 1 || i == 0 || j == 0)
            {
                Actor* wall = Actor::Create("wall");
                wall->SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
                
                /** SetPosition sets the center of the sprite, thus we have to add half the width/height. */
                Vector2 pos = GridToWorldSpace(Vector2(i, j));
                wall->SetPosition(pos);
                
                theWorld.Add(wall, layer + 1);
                AddActor(wall);
            }
        }
    }
}

void
Grid::Update(float dt)
{
    /** Clear the grid before the next frame update. */
    for(int i = 0; i < m_width; ++i)
    {
        for(int j = 0; j < m_height; ++j)
        {
            std::set<Actor*>& cellOccupiers = m_collisionGrid[i][j];
            cellOccupiers.clear();
        }
    }
    
    /** Mark each actor on its current grid position. */
    std::vector<Actor*>::iterator it = m_actors.begin();
    for(; it != m_actors.end(); ++it)
    {
        /** Convenience alias. */
        Actor* actor = *it;
        
        Vector2 coords = WorldSpaceToGrid(m_intermediatePositions[actor]);
        
        /** SetPosition sets the center of the sprite, thus we have to add half the width/height. */
        Vector2 worldPos = GridToWorldSpace(coords) + actor->GetSize() / 2;
        
        /** Snap all actors positions to the grid. */
        actor->SetPosition(worldPos);
        
        /** 
         * Cast is safe because grid space is integer values only - its necessary due to lack of vec2i class. 
         * values from WorldSpaceToGrid will always be in the range [0, m_width) x [0, m_height).
         */
        m_collisionGrid[static_cast<int>(coords.X)][static_cast<int>(coords.Y)].insert(actor);
    }
    
    /** Evaluate every grid cell for collisions. */
    for(int i = 0; i < m_width; ++i)
    {
        for(int j = 0; j < m_height; ++j)
        {
            std::set<Actor*>& cellOccupiers = m_collisionGrid[i][j];

            /** More than one occupier means a collision occured. */
            if(cellOccupiers.size() > 1)
            {
                /** 
                 * Dispatch a collision message for every detected collision,
                 * containing all the actors part of the collision.
                 */
                TypedMessage<std::set<Actor*> >* collisionMessage =
                    new TypedMessage<std::set<Actor*> >("GridCollision",
                                                        cellOccupiers);
                
                theSwitchboard.Broadcast(collisionMessage);
            }
        }
    }
}

Vector2
Grid::GetSize() const
{
    return Vector2(m_width, m_height);
}

bool
Grid::isCellOccupied(int i, int j)
{
    return m_collisionGrid[i][j].size() != 0;
}

void
Grid::AddActor(Actor* actor)
{
    m_actors.push_back(actor);
    m_intermediatePositions[actor] = actor->GetPosition();
}

void
Grid::RemoveActor(Actor* actor)
{
    m_actors.erase(std::remove(m_actors.begin(), m_actors.end(), actor), m_actors.end());
    positionMapType::iterator it = m_intermediatePositions.find(actor);
    
    if(it != m_intermediatePositions.end())
    {
        m_intermediatePositions.erase(it);
    }
}

void
Grid::SetIntermediatePosition(Actor* actor, Vector2 position)
{
    positionMapType::const_iterator it = m_intermediatePositions.find(actor);
    
    /** Do nothing if the actor is not an entity within the grid already. */
    if(it == m_intermediatePositions.end())
    {
        return;
    }
    
    m_intermediatePositions[actor] = position;
}

Vector2
Grid::GetIntermediatePosition(Actor* actor) const
{
    positionMapType::const_iterator it = m_intermediatePositions.find(actor);
    
    /**
     * Return (0, 0) for actors that are not registered with the grid.
     */
    if(it == m_intermediatePositions.end())
    {
        return Vector2(0, 0);
    }
    
    return it->second;
}

Vector2
Grid::GetUnitSize() const
{
    Vector2 max = theCamera.GetWorldMaxVertex();
    
    const float kUnitLengthX = max.X * 2  / m_width;
    const float kUnitLengthY = max.Y * 2  / m_height;
    
    return Vector2(kUnitLengthX, kUnitLengthY);
}

Vector2
Grid::WorldSpaceToGrid(Vector2 pos) const
{
#define CLAMP(x, minval, maxval) (MIN(MAX(minval, x), maxval))
    Vector2 max = theCamera.GetWorldMaxVertex();
    
    /** Times two because the origin is the center of the screen in Angel. */
    const float kUnitLengthX = max.X * 2 / m_width;
    const float kUnitLengthY = max.Y * 2 / m_height;
    
    /** Shift by half the area (Negative axis) and divide by unit length. */
    pos.X = round((pos.X + max.X) / kUnitLengthX);
    pos.Y = round((pos.Y + max.Y) / kUnitLengthY);
    
    /** Clamp values that are outside of the grid. */
    pos.X = CLAMP(pos.X, 0, m_width - 1);
    pos.Y = CLAMP(pos.Y, 0, m_height - 1);
    
#undef CLAMP
    return pos;
}

Vector2
Grid::GridToWorldSpace(Vector2 pos) const
{
    Vector2 max = theCamera.GetWorldMaxVertex();
    
    const float kUnitLengthX = max.X * 2  / m_width;
    const float kUnitLengthY = max.Y * 2  / m_height;
    
    /** Shift by half the area (Negative axis) and divide by unit length. */
    pos.X = pos.X * kUnitLengthX - max.X;
    pos.Y = pos.Y * kUnitLengthY - max.Y;
    
    return pos;
}