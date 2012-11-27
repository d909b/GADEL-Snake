/**
 *  Food.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include "Consumable.h"

/**
* @class Food
*
* @description Implementation of class Food.
*/
class Food : public Actor, public Consumable
{
public:
    Food(Vector2 position);
	virtual void performConsumption(Snake* snake) const;
private:
};