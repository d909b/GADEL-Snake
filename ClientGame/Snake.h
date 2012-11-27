/**
 *  Snake.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include <deque>

class Consumable;
class Grid;

/**
* @class Snake
*
* @description Implementation of class Snake.
*/
class Snake : public Actor
{
public:
    enum Direction
    {
        DirectionUp,
        DirectionDown,
        DirectionLeft,
        DirectionRight
    };
    
	Snake(Grid* grid);
	~Snake();
    
    void Consume(Consumable* consumable);
    virtual void Update(float dt);
    virtual void ReceiveMessage(Message* m);
private:
    void handleCollision(Message* m);
    void handleConsumedFood(Message* m);
    void handleChangeDirection(Direction direction);
    
    Grid* m_grid;
    Direction m_direction;
    float m_movespeed;
    std::deque<Actor*> m_tail;
};