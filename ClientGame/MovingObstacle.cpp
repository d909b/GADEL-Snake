//
//  MovingObstacle.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 14.01.13.
//
//

#include "MovingObstacle.h"

MovingObstacle::MovingObstacle(Vector2 startPosition, Vector2 direction, float speed, float distance, char* sprite_path, Snake* snake)
    : m_direction(direction), m_speed(abs(speed)), m_distance(abs(distance)), m_movementCount(0), m_maxMovements((m_distance / speed) * 60), m_snake(snake)
{
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    SetPosition(startPosition);
    SetSprite(sprite_path);
}


void MovingObstacle::Update(float dt)
{
    if(this->IsDestroyed() || m_snake == NULL)
    {
        return;
    }
    
    Actor::Update(dt);
    const float rotation = GetRotation();
    SetRotation((rotation + 190 * dt));
    
    Vector2 position = GetPosition();
    
    position += m_direction * (m_speed * dt);
    
    SetPosition(position);
    
    
    if(++m_movementCount % m_maxMovements == 0)
    {
        m_direction *= -1;
    }
    
    if(m_snake->collided(this))
    {
        m_snake->collide();
    }    
}