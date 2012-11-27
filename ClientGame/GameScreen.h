/**
 *  GameScreen.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include "SnakesGameManager.h"

/**
* @class GameScreen
*
* @description Implementation of class GameScreen.
*/
class GameScreen : public SnakesScreen
{
public:
	void Start();
    void Update(float dt);
private:
    Actor* m_snake;
    TextActor* m_highscore;
};