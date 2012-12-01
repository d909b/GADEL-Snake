/**
 *  Snake.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "Snake.h"
#include <set>
#include "Consumable.h"
#include "Grid.h"

Snake::Snake(Grid* grid) :
    m_grid(grid),
    m_direction(DirectionUp),
    m_movespeed(10.f)
{
    SetColor(0, 0, 0);
    SetDrawShape(ADS_Square);
    
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    SetPosition(0, 0);
    
	theSwitchboard.SubscribeTo(this, "GridCollision");
    theSwitchboard.SubscribeTo(this, "FoodConsumed");
    theSwitchboard.SubscribeTo(this, "MoveUp");
    theSwitchboard.SubscribeTo(this, "MoveDown");
    theSwitchboard.SubscribeTo(this, "MoveLeft");
    theSwitchboard.SubscribeTo(this, "MoveRight");
}

Snake::~Snake()
{
	;
}

void
Snake::Update(float dt)
{
    Vector2 pos = m_grid->GetIntermediatePosition(this);
    Vector2 oldPos = pos;
    Vector2 oldGridPos = m_grid->WorldSpaceToGrid(pos);
    
    switch(m_direction)
    {
        case DirectionUp:
            pos.Y += m_movespeed * dt;
            break;
        case DirectionDown:
            pos.Y -= m_movespeed * dt;
            break;
        case DirectionLeft:
            pos.X -= m_movespeed * dt;
            break;
        case DirectionRight:
            pos.X += m_movespeed * dt;
            break;
    }
    
    m_grid->SetIntermediatePosition(this, pos);
    Vector2 newGridPos = m_grid->WorldSpaceToGrid(pos);
    
    if(oldGridPos != newGridPos)
    {
        /** The snake head has moved a cell. Adjust the tail. */
        std::deque<Actor*>::iterator it = m_tail.begin();
        
        Vector2 prior = oldPos;
        for(; it != m_tail.end(); ++it)
        {
            /** Shift all tail members to the position of the member prior to itself. */
            Vector2 tmp = m_grid->GetIntermediatePosition(*it);
            m_grid->SetIntermediatePosition(*it, prior);
            prior = tmp;
        }
    }
}

void
Snake::Consume(Consumable* consumable)
{
    consumable->performConsumption(this);
}

void
Snake::handleCollision(Message* m)
{
    TypedMessage<std::set<Actor*> >* msg = static_cast<TypedMessage<std::set<Actor*> >* >(m);
    
    std::set<Actor*> collisions = msg->GetValue();
    
    std::set<Actor*>::iterator it = collisions.find(this);
    if(it != collisions.end())
    {
        /** Remove self from the set of collided objects. */
        collisions.erase(it);
        
        it = collisions.begin();
        for(; it != collisions.end(); ++it)
        {
            Consumable* consumable = dynamic_cast<Consumable*>(*it);
            
            /** Consume the object if it is a consumable. */
            if(consumable != NULL)
            {
                Consume(consumable);
            }
            /** If the object is not consumable we've hit an obstacle. */
            else
            {
                theSwitchboard.Broadcast(new Message("ObstacleHit"));
            }
        }
    }
    else
    {
        /** The snake is not part of this collision. */
        return;
    }
}

void
Snake::handleConsumedFood(Message* m)
{
    /** Increase length of the trailing tail */
    Actor* tail = new Actor();
    tail->SetColor(1, 0, 0);
    
    if(m_tail.size() == 0)
    {
        tail->SetDrawShape(ADS_Circle);
    }
    else
    {
        tail->SetDrawShape(ADS_Square);
    }
    
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    tail->SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));;
    tail->SetPosition(m_grid->GetIntermediatePosition(this));
    m_grid->AddActor(tail);
    theWorld.Add(tail);
    m_tail.push_front(tail);
}

void
Snake::handleChangeDirection(Direction direction)
{    
    /** Only change if the direction is not opposing to the current direction. */
    switch(direction)
    {
        case DirectionUp:
            if(m_direction == DirectionDown)
            {
                return;
            }
            break;
        case DirectionDown:
            if(m_direction == DirectionUp)
            {
                return;
            }
            break;
        case DirectionLeft:
            if(m_direction == DirectionRight)
            {
                return;
            }
            break;
        case DirectionRight:
            if(m_direction == DirectionLeft)
            {
                return;
            }
            break;
    }
    
	m_direction = direction;
}

void
Snake::ReceiveMessage(Message* m)
{
	if(m->GetMessageName() == "GridCollision")
    {
        handleCollision(m);
    }
    if(m->GetMessageName() == "FoodConsumed")
    {
        handleConsumedFood(m);
    }
    if(m->GetMessageName() == "MoveUp")
    {
        handleChangeDirection(DirectionUp);
    }
    if(m->GetMessageName() == "MoveDown")
    {
        handleChangeDirection(DirectionDown);
    }
    if(m->GetMessageName() == "MoveLeft")
    {
        handleChangeDirection(DirectionLeft);
    }
    if(m->GetMessageName() == "MoveRight")
    {
        handleChangeDirection(DirectionRight);
    }
}
