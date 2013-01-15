//
//  SlowPowerup.h
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#ifndef __ClientGame__SlowPowerup__
#define __ClientGame__SlowPowerup__

#include <iostream>
#include "Powerup.h"

class SlowPowerup : public Powerup
{
public:
    SlowPowerup(Vector2 position, unsigned int ttl_milliseconds);
    virtual void applyEffect(Snake* snake);
    virtual void undoEffect(Snake* snake);

private:
    float m_original_movespeed;
};

#endif /* defined(__ClientGame__SlowPowerup__) */
