//
//  CirclingObstacle.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 15.01.13.
//
//

#include "CirclingObstacle.h"

CirclingObstacle::CirclingObstacle(Vector2 center, float speed, float radius, char* sprite_path, Snake* snake)
    : m_center(center), m_speed(abs(speed)), m_radius(abs(radius)), m_snake(snake), m_theta(0)
{
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    SetPosition(center);
    SetSprite(sprite_path);
}

void CirclingObstacle::Update(float dt)
{
    if(this->IsDestroyed() || m_snake == NULL)
    {
        return;
    }
    
    Actor::Update(dt);
    
    //Set own rotation
    const float rotation = GetRotation();
    SetRotation((rotation + 190 * dt));
    
    //New position to calculate for the circle motion
    Vector2 position = Vector2(m_center.X, m_center.Y);
    
    const Vector2 size = GetSize();
    position.X = size.X + m_radius * sin(m_theta -  atan(size.X/size.Y));
    position.Y = size.Y - m_radius * cos(m_theta - atan(size.X/size.Y));
    
    m_theta += m_speed * dt;
    
    if(m_theta >= 360){
        m_theta = 0;
    }
    
    SetPosition(position);
    
    if(!m_snake->isInvulnerable() && m_snake->collided(this))
    {
        m_snake->collide();
    }
}