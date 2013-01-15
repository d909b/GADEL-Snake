/**
 *  LevelScreen.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include "SnakesGameManager.h"
#include "Grid.h"
#include "Snake.h"
#include "FoodGenerator.h"
#include "StatusBox.h"



/**
* @class LevelScreen
*
* @description Implementation of class LevelScreen.
*/
class LevelScreen : public SnakesScreen, public MessageListener
{
public:
    LevelScreen();
    ~LevelScreen();

    void Update(float dt);
    void Render();
    
    virtual void ReceiveMessage(Message* m);
private:
    TextActor* m_highscore;
    Grid m_grid;
    Snake* m_snake;
    FoodGenerator m_foodGenerator;
    uint32_t m_highscoreCounter;
    TextActor* m_popupText;
    StatusBox* m_statusbox;
};