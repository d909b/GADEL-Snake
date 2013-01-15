/**
 *  SnakesGameManager.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include "SnakesScreen.h"

/**
* @class SnakesGameManager
*
* @description Implementation of class SnakesGameManager.
*/
class SnakesGameManager : public GameManager
{
public:
	SnakesGameManager();
    ~SnakesGameManager();
	
    virtual void Update(float dt);
	virtual void Render();
    
	virtual void SoundEnded(AngelSoundHandle sound);
	virtual void ReceiveMessage(Message* message);
    
    //Game-Structure methods
    void replaceScreen(SnakesScreen* screen);
    void showMenu();
    void startLevel(int lvl_number); //Starts a new level    
    
private:
    //Stores the reference to the current displayed screen - This screen is the only one to be rendered / updated
    SnakesScreen* m_currentScreen;
};
