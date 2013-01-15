//
//  StatusBox.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 12.01.13.
//
//

#include "StatusBox.h"
#include <list>

unsigned int const size = 32; //Square size of the tile
unsigned int const padding = 5; //Pixel

StatusBox::StatusBox(Vector2 position, Snake* snake, const unsigned int max_powerups) : m_snake(snake), m_max_powerups(max_powerups)
{
    SetPosition(position);
    
    SetSize(MathUtil::ScreenToWorld(max_powerups * size + max_powerups * padding, size));

}

StatusBox::~StatusBox()
{
    ;
}

void StatusBox::Update(float dt)
{
    std::list<Powerup*> powerups = m_snake->getCurrentPowerups();
    
    std::list<Powerup*>::iterator it = powerups.begin();
    
    Vector2 current_pos = GetPosition(); //Position of the StatusBox for relative position calculation
    
    //Tile the powerups in a row
    for(int i=0; it != powerups.end() && i <= m_max_powerups; ++it, ++i)
    {
        //Vector2 relativePosition(current_pos.X + (size * i) + padding , current_pos.Y);
        //(*it)->SetPosition(current_pos);
    }

}

void StatusBox::ReceiveMessage(Message* m){
    
}



void StatusBox::Render(){
    Actor::Render();
    
    std::list<Powerup*> powerups = m_snake->getCurrentPowerups();
    
    //TODO: DOES NOT INTEND EACH ELEMENT, WHYSOEVER
    std::list<Powerup*>::iterator it = powerups.begin();
    Vector2 current_pos = GetPosition(); //Position of the StatusBox for relative position calculation
    //Tile the powerups in a row
    for(int i=0; it != powerups.end() && i <= m_max_powerups; ++it, ++i)
    {
        Vector2 relativePosition(current_pos.X + (size * i) + padding + 1000 , current_pos.Y);
        (*it)->SetPosition(current_pos);
        (*it)->Render();
    }
}