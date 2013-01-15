//
//  ScoreDoublePowerup.h
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#ifndef __ClientGame__ScoreDoublePowerup__
#define __ClientGame__ScoreDoublePowerup__

#include <iostream>

#include "Powerup.h"

class ScoreDoublePowerup : public Powerup
{
public:
    ScoreDoublePowerup(Vector2 position, unsigned int ttl_milliseconds);
    virtual void applyEffect(Snake* snake);
    virtual void undoEffect(Snake* snake);

private:
    unsigned int m_original_Multiplicator;
    
};

#endif /* defined(__ClientGame__ScoreDoublePowerup__) */
