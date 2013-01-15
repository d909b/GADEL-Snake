/**
 *  Food.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "Food.h"

Food::Food(Vector2 position) : Consumable(position, "Resources/Images/food/food_normal.png")
{
    ;
}

void 
Food::performConsumption(Snake* snake)
{
    theSwitchboard.Broadcast(new Message("FoodConsumed"));
}