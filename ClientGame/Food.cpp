/**
 *  Food.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "Food.h"

Food::Food(Vector2 position)
{
    SetColor(0, 0, 1);
    SetDrawShape(ADS_Circle);
    SetSize(1.);
    SetPosition(position);
}

void 
Food::performConsumption(Snake* snake) const
{
    theSwitchboard.Broadcast(new Message("FoodConsumed"));
}