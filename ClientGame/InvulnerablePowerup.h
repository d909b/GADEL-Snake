//
//  InvulnerabelPowerup.h
//  ClientGame
//
//  Created by Patrick Stapfer on 15.01.13.
//
//

#ifndef __ClientGame__InvulnerablePowerup__
#define __ClientGame__InvulnerablePowerup__

#include <iostream>
#include "Snake.h"

class InvulnerablePowerup : public Powerup
{
public:
    InvulnerablePowerup(Vector2 position, unsigned int ttl_milliseconds);
    virtual void applyEffect(Snake* snake);
    virtual void undoEffect(Snake* snake);
};

#endif /* defined(__ClientGame__InvulnerabelPowerup__) */
