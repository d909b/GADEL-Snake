//
//  InvulnerabelPowerup.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 15.01.13.
//
//

#include "InvulnerablePowerup.h"

InvulnerablePowerup::InvulnerablePowerup(Vector2 position, unsigned int ttl_milliseconds)
: Powerup(position, ttl_milliseconds, "Invulnerability", "Resources/Images/Food/invulnerable_powerup.png")
{
    ;
}

void InvulnerablePowerup::applyEffect(Snake *snake)
{
    snake->setInvulnerable(true);
}

void InvulnerablePowerup::undoEffect(Snake *snake)
{
    snake->setInvulnerable(false);
}