//
//  Consumable.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 12.01.13.
//
//

#include "Consumable.h"

Consumable::Consumable(Vector2 position, char* sprite_path)
{
    const float kVerticesPerPixelX = theCamera.GetWorldMaxVertex().X * 2 / theCamera.GetWindowWidth();
    const float kVerticesPerPixelY = theCamera.GetWorldMaxVertex().Y * 2 / theCamera.GetWindowHeight();
    
    SetSize(Vector2(32 * kVerticesPerPixelX, 32 * kVerticesPerPixelY));
    SetPosition(position);
    SetSprite(sprite_path);
}