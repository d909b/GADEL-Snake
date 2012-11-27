/**
 *  MenuScreen.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include <stdint.h>
#include "SnakesGameManager.h"

/**
* @class MenuScreen
*
* @description Implementation of class MenuScreen.
*/
class MenuScreen : public SnakesScreen, public MessageListener
{
public:
    MenuScreen();
    virtual void Start();
    virtual void ReceiveMessage(Message* m);
private:
    bool m_isStartGame;
    bool m_messageSent;
    TextActor* m_start;
    TextActor* m_highscore;
};