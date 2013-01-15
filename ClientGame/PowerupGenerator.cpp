//
//  PowerupGenerator.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#include "PowerupGenerator.h"
#include "ScoreDoublePowerup.h"
#include "FastPowerup.h"
#include "SlowPowerup.h"


Powerup* PowerupGenerator::produce(PowerupType type, Vector2 position, int ttl_milliseconds)
{
    switch(type)
    {
        case DOUBLE_SCORE:
            return new ScoreDoublePowerup(position, ttl_milliseconds);
        case FASTER_MOVEMENT:
            return new FastPowerup(position, ttl_milliseconds);
        case SLOWER_MOVEMENT:
            return new SlowPowerup(position, ttl_milliseconds);
        default:
            return NULL;
    }
}