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
class Consumable : public Actor
{
public:
    Consumable(Vector2 position, char* sprite_path);
    
    /** Implement this to perform the consumption's side effects. */
	virtual void performConsumption(Snake* snake) = 0;
private:
};