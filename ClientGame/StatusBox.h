//
//  StatusBox.h
//  ClientGame
//
//  Created by Patrick Stapfer on 12.01.13.
//
//

#ifndef __ClientGame__StatusBox__
#define __ClientGame__StatusBox__

#include <iostream>
#include "Snake.h"

class StatusBox : public Actor
{
public:
    StatusBox(Vector2 position, Snake* snake, const unsigned int max_powerups);
    ~StatusBox();
    void Update(float dt);
    
    virtual void Render();
    virtual void ReceiveMessage(Message* m);
    
private:   
    //Snake to represent the status
    Snake* m_snake;
    
    //How many powerups can be displayed in the box
    const unsigned int m_max_powerups;
};

#endif /* defined(__ClientGame__StatusBox__) */


