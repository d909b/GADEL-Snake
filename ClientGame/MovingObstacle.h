//
//  MovingObstacle.h
//  ClientGame
//
//  Created by Patrick Stapfer on 14.01.13.
//
//

#ifndef __ClientGame__MovingObstacle__
#define __ClientGame__MovingObstacle__

#include <iostream>

#include "Snake.h"


class MovingObstacle : public Actor
{
public:
    MovingObstacle(Vector2 startPosition, Vector2 direction, float speed, float distance, char* sprite_path, Snake* snake);
    
    virtual void Update(float dt);
    
private:
    Vector2 m_direction;
    float m_speed;
    float m_distance;
    int m_movementCount;
    const int m_maxMovements;
    Snake* m_snake;
};

#endif /* defined(__ClientGame__MovingObstacle__) */
