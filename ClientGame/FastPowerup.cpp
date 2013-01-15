//
//  FastPowerup.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#include "FastPowerup.h"


FastPowerup::FastPowerup(Vector2 position, unsigned int ttl_milliseconds)
    : Powerup(position, ttl_milliseconds, "Fast Movement", "Resources/Images/Food/fast_powerup.png"), m_original_movespeed(10.f)
{
    ;
}

void FastPowerup::applyEffect(Snake *snake)
{
    m_original_movespeed = snake->GetMoveSpeed();
    snake->SetMoveSpeed(m_original_movespeed * 1.4);
}

void FastPowerup::undoEffect(Snake *snake)
{
    snake->SetMoveSpeed(m_original_movespeed);
}


