//
//  SlowPowerup.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#include "SlowPowerup.h"

SlowPowerup::SlowPowerup(Vector2 position, unsigned int ttl_milliseconds)
    : Powerup(position, ttl_milliseconds, "Slow Movement", "Resources/Images/Food/slow_powerup.png"), m_original_movespeed(10.f)
{
    ;
}

void SlowPowerup::applyEffect(Snake *snake)
{
    m_original_movespeed = snake->GetMoveSpeed();
    snake->SetMoveSpeed(m_original_movespeed / 1.5);
}

void SlowPowerup::undoEffect(Snake *snake)
{
    snake->SetMoveSpeed(m_original_movespeed);
}