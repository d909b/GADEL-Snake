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

Grid::Grid(uint32_t width, uint32_t height) :
    m_width(width),
    m_height(height)
{
    /** Reserve memory for the grid. */
    m_collisionGrid = new std::vector<Actor*>*[m_width];
    
    for(uint32_t i = 0; i < m_width; ++i)
    {
        m_collisionGrid[i] = new std::vector<Actor*>[m_height];
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
Grid::Update(float dt)
{
    std::vector<Actor*>::iterator it = m_actors.begin();
    for(; it != m_actors.end(); ++it)
    {
        /** Convenience alias. */
        Actor* actor = *it;
        
        Vector2 coords = WorldSpaceToGrid(m_intermediatePositions[actor]);
        
        /** Snap all actors positions to the grid. */
        actor->SetPosition(GridToWorldSpace(coords));
        
        /** Cast is safe because grid space is integer values only, necessary due to lack of vec2i class. */
        m_collisionGrid[static_cast<int>(coords.X)][static_cast<int>(coords.Y)].push_back(actor);
    }
    
    for(int i = 0; i < m_width; ++i)
    {
        for(int j = 0; j < m_height; ++j)
        {
            std::vector<Actor*>& cellOccupiers = m_collisionGrid[i][j];

            /** More than one occupier means a collision occured. */
            if(cellOccupiers.size() > 1)
            {
                /** 
                 * Dispatch a collision message for every detected collision.
                 */
                TypedMessage<std::vector<Actor*> >* collisionMessage =
                    new TypedMessage<std::vector<Actor*> >("GridCollision",
                                                           cellOccupiers);
                
                theSwitchboard.Broadcast(collisionMessage);
            }
            
            /** Clear for the next run. */
            cellOccupiers.clear();
        }
    }
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
    
    if(it == m_intermediatePositions.end())
    {
        return Vector2(0, 0);
    }
    
    return it->second;
}

Vector2
Grid::WorldSpaceToGrid(Vector2 pos) const
{
#define CLAMP(x, minval, maxval) (MIN(MAX(minval, x), maxval))
    Vector2 max = theCamera.GetWorldMaxVertex();
    
    const float kUnitLengthX = max.X * 2 / m_width;
    const float kUnitLengthY = max.Y * 2 / m_height;
    
    /** Shift by half the area (Negative axis) and divide by unit length. */
    pos.X = round(pos.X + max.X / kUnitLengthX);
    pos.Y = round(pos.Y + max.Y / kUnitLengthY);
    
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