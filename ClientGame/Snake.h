/**
 *  Snake.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include <queue>
#include <deque>
#include <list>
#include "Powerup.h"

class Powerup;
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
        DirectionUp = 0,
        DirectionDown,
        DirectionLeft,
        DirectionRight
    };
    
	Snake(Grid* grid);
	~Snake();
    
    void stop();
    void Consume(Consumable* consumable);
    virtual void Update(float dt);
    virtual void Render();
    virtual void ReceiveMessage(Message* m);
    
    /*
      This method applies the effect of the powerup
     */
    void addPowerup(Powerup* powerup);
    void updatePowerups(float dt);
    
    //Collision methods
    void collide();
    bool collided(Actor* actor);
    
    //Getter, Setter
    unsigned int getPointMultiplicator();
    void setPointMultiplicator(unsigned int);
    std::list<Powerup*> getCurrentPowerups();
    float GetMoveSpeed();
    void SetMoveSpeed(float speed);
    
private:
    bool isOppositeDirection(Direction direction);
    void handleCollision(Message* m);
    void handleConsumedFood(Message* m);
    void handleChangeDirection(Direction direction);
    void chooseCornerOrientation(Actor* current, float priorRot, Vector2 priorPos);
    Actor* addTailPiece(Vector2 position);
    
    Grid* m_grid;
    Direction m_direction;
    std::queue<Direction> m_requestedDirections;
    const uint32_t m_inputBufferMaxSize;
    float m_movespeed;
    std::deque<Actor*> m_tail;
    int m_biteTimer;
    int m_numConsumed;
    bool m_isStopped;
    unsigned int m_pointMultiplicator;
    std::list<Powerup*> m_current_powerups;
};