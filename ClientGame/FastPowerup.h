//
//  FastPowerup.h
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#ifndef __ClientGame__FastPowerup__
#define __ClientGame__FastPowerup__

#include <iostream>
#include "Powerup.h"

class FastPowerup : public Powerup
{
public:
    FastPowerup(Vector2 position, unsigned int ttl_milliseconds);
    virtual void applyEffect(Snake* snake);
    virtual void undoEffect(Snake* snake);
private:
    float m_original_movespeed;
};
#endif /* defined(__ClientGame__FastPowerup__) */
