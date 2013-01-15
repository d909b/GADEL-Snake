/**
 *  PowerUp.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "Powerup.h"

Powerup::Powerup(Vector2 position, unsigned int ttl_milliseconds, String description)
    : Consumable(position, "Resources/Images/food/powerup.png"),
      m_ttl(ttl_milliseconds),
      m_description(description)
{
    ;
}

Powerup::Powerup(Vector2 position, unsigned int ttl_milliseconds, String description, char* file_path)
: Consumable(position, file_path),
m_ttl(ttl_milliseconds),
m_description(description)
{
    ;
}

void Powerup::decreaseTTL(unsigned int milliseconds)
{
    if(milliseconds <= m_ttl)
    {
        m_ttl -= milliseconds;
    }
    else{
        m_ttl = 0;
    }
}

std::string Powerup::getDescription()
{
    return m_description;
}

int Powerup::getTTL()
{
    return m_ttl;
}

void Powerup::setTTL(unsigned int milliseconds)
{
    m_ttl = milliseconds;
}

bool Powerup::isTTLexceeded()
{
    return m_ttl == 0;
}

void Powerup::performConsumption(Snake* snake) 
{
    snake->addPowerup(this);
    theSwitchboard.Broadcast(new Message("PowerupConsumed", (MessageListener *)this));
}