/**
 *  GameScreen.h
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

/**
* @class GameScreen
*
* @description Implementation of class GameScreen.
*/
class GameScreen : public SnakesScreen, public MessageListener
{
public:
    GameScreen();
	void Start();
    void Update(float dt);
    void Render();
    virtual void ReceiveMessage(Message* m);
private:
    TextActor* m_highscore;
    Grid m_grid;
    Snake* m_snake;
    FoodGenerator m_foodGenerator;
    uint32_t m_highscoreCounter;
};