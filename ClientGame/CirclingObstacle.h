//
//  CirclingObstacle.h
//  ClientGame
//
//  Created by Patrick Stapfer on 15.01.13.
//
//

#ifndef __ClientGame__CirclingObstacle__
#define __ClientGame__CirclingObstacle__

#include <iostream>
#include "Snake.h"

class CirclingObstacle : public Actor
{
public:
    CirclingObstacle(Vector2 center, float speed, float radius, char* sprite_path, Snake* snake);
    
    virtual void Update(float dt);
    
private:
    Vector2 m_center;
    float m_speed;
    float m_radius;
    Snake* m_snake;
    float m_theta;
};

#endif /* defined(__ClientGame__CirclingObstacle__) */
