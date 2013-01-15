/**
 *  PowerUp.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include <string>
#include "Consumable.h"
#include "Snake.h"

/**
* @class PowerUp
*
* @description Implementation of class PowerUp.
*/
class Powerup : public Consumable
{
public:
	Powerup(Vector2 position, unsigned int ttl_milliseconds, String description);
    Powerup(Vector2 position, unsigned int ttl_milliseconds, String description, char* file_path);
    
    virtual void performConsumption(Snake* snake);
    
    virtual void applyEffect(Snake* snake) = 0;
    virtual void undoEffect(Snake* snake) = 0;
    
    //Decreases the Time-To-Live of the powerup
    void decreaseTTL(unsigned int milliseconds);
    
    //Getter, Setter
    String getDescription();
    void setTTL(unsigned int milliseconds);
    int getTTL();
    
    //Utility
    bool isTTLexceeded();
    
    
private:
    
    //Time-To-Live in milliseconds
    unsigned int m_ttl;
    String m_description;
};