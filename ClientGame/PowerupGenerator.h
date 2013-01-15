//
//  PowerupGenerator.h
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#ifndef ClientGame_PowerupGenerator_h
#define ClientGame_PowerupGenerator_h

#include "Powerup.h"

enum PowerupType
{
    DOUBLE_SCORE,
    FASTER_MOVEMENT,
    SLOWER_MOVEMENT,
    INVULNERABLE,
    _LAST
};

class PowerupGenerator
{
public:
    //Returns a new allocated Powerup object - The caller has to free the memory himself
    static Powerup* produce(PowerupType type, Vector2 position, int ttl_milliseconds);
};

#endif
