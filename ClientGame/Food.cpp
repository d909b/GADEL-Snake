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
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    SetPosition(position);
    SetSprite("Resources/Images/food/food_normal.png");
}

void 
Food::performConsumption(Snake* snake) const
{
    theSwitchboard.Broadcast(new Message("FoodConsumed"));
}