/**
 *  Consumable.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

class Snake;

/**
* @class Consumable
*
* @description Implementation of class Consumable.
*/
class Consumable
{
public:
    /** Implement this to perform the consumption's side effects. */
	virtual void performConsumption(Snake* snake) const = 0;
private:
};