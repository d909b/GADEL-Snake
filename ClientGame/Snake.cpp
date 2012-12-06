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
    m_inputBufferMaxSize(3),
    m_movespeed(10.f),
    m_numConsumed(0),
    m_isStopped(false)
{
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    SetPosition(0, 0);
    SetSprite("Resources/Images/snake/snake_head.png");
    
    Vector2 offset(0, -m_grid->GetUnitSize().Y);
    Actor* t = addTailPiece(offset*3.f);
    t = addTailPiece(offset*2.f);
    t = addTailPiece(offset);
    
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
    if(m_isStopped)
    {
        return;
    }
    
    Vector2 pos = m_grid->GetIntermediatePosition(this);
    Vector2 oldPos = pos;
    Vector2 oldGridPos = m_grid->WorldSpaceToGrid(pos);
    
    float rot = 0;
    switch(m_direction)
    {
        case DirectionUp:
            pos.Y += m_movespeed * dt;
            break;
        case DirectionDown:
            pos.Y -= m_movespeed * dt;
            rot = 180;
            break;
        case DirectionLeft:
            pos.X -= m_movespeed * dt;
            rot = 90;
            break;
        case DirectionRight:
            pos.X += m_movespeed * dt;
            rot = 270;
            break;
    }
    
    m_grid->SetIntermediatePosition(this, pos);
    Vector2 newGridPos = m_grid->WorldSpaceToGrid(pos);
    
    if(oldGridPos != newGridPos)
    {
        /** Only update the rotation on positional changes. */
        SetRotation(rot);
        
        if(!m_requestedDirections.empty())
        {
            while(isOppositeDirection(m_requestedDirections.front()))
            {
                m_requestedDirections.pop();
                
                if(m_requestedDirections.empty())
                {
                    break;
                }
            }
            
            if(!m_requestedDirections.empty())
            {
                m_direction = m_requestedDirections.front();
                m_requestedDirections.pop();
            }
        }
        
        if(m_biteTimer > 1)
        {
            SetSprite("Resources/Images/snake/snake_head.png");
        }
        
        m_biteTimer++;
        
        /** The snake head has moved a cell. Adjust the tail. */
        std::deque<Actor*>::iterator it = m_tail.begin();
        
        Vector2 prior = oldPos;
        float priorRot = GetRotation();
        
        /** Insert a tailpiece right after the head. */
        if(m_numConsumed != 0)
        {
            addTailPiece(prior);
            m_numConsumed--;
        }
        else
        {
            for(; it != m_tail.end(); ++it)
            {
                /** Shift all tail members to the position of the member prior to itself. */
                Vector2 tmp = m_grid->GetIntermediatePosition(*it);
                m_grid->SetIntermediatePosition(*it, prior);
                
                float tmpRot = (*it)->GetRotation();
                
                bool isCorner = false;
                if(*it != m_tail.back())
                {
                    if(tmpRot != priorRot)
                    {
                        chooseCornerOrientation(*it, priorRot, prior);
                        isCorner = true;
                    }
                    else
                    {
                        (*it)->SetSprite("Resources/Images/snake/snake_body.png");
                    }
                }
                
                (*it)->SetRotation(priorRot);
                
                priorRot = tmpRot;
                prior = tmp;
            }
        }
    }
}

void
Snake::chooseCornerOrientation(Actor *current, float priorRot, Vector2 priorPos)
{
    bool isLeftTurn = false;
    
    isLeftTurn = current->GetRotation() < priorRot;
    
    /** Handle the corner cases properly aswell. */
    if(current->GetRotation() == 270 && priorRot == 0)
    {
        isLeftTurn = true;
    }
    
    if((current->GetRotation() == 0 && priorRot == 270))
    {
        isLeftTurn = false;
    }
    
    if(isLeftTurn)
    {
        current->SetSprite("Resources/Images/snake/snake_corner270.png");
    }
    else
    {
        current->SetSprite("Resources/Images/snake/snake_corner.png");
    }
}

void
Snake::Consume(Consumable* consumable)
{
    m_biteTimer = 0;
    SetSprite("Resources/Images/snake/snake_head_bite.png");
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
    m_numConsumed++;
}

bool
Snake::isOppositeDirection(Direction direction)
{
    switch(direction)
    {
        case DirectionUp:
            if(m_direction == DirectionDown)
            {
                return true;
            }
            break;
        case DirectionDown:
            if(m_direction == DirectionUp)
            {
                return true;
            }
            break;
        case DirectionLeft:
            if(m_direction == DirectionRight)
            {
                return true;
            }
            break;
        case DirectionRight:
            if(m_direction == DirectionLeft)
            {
                return true;
            }
            break;
    }
    
    return false;
}

Actor*
Snake::addTailPiece(Vector2 position)
{
    /** Increase length of the trailing tail */
    Actor* tail = new Actor();
    
    if(m_tail.size() == 0)
    {
        tail->SetSprite("Resources/Images/snake/snake_tail.png");
    }
    else
    {
        tail->SetSprite("Resources/Images/snake/snake_body.png");
    }
    
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    tail->SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    tail->SetPosition(position);
    tail->SetRotation(GetRotation());
    m_grid->AddActor(tail);
    
    if(m_tail.size() == 0)
    {
        theWorld.Add(tail, 2);
    }
    else
    {
        theWorld.Add(tail);
    }
    
    m_tail.push_front(tail);
    
    return tail;
}

void
Snake::handleChangeDirection(Direction direction)
{    
    /** Inputs are buffered until the next position update. */
	m_requestedDirections.push(direction);
    
    if(m_requestedDirections.size() > m_inputBufferMaxSize)
    {
        m_requestedDirections.pop();
    }
}

void
Snake::stop()
{
    m_isStopped = true;
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
