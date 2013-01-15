/**
 *  SnakesGameManager.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "SnakesGameManager.h"
#include "SnakesScreen.h"
#include "MenuScreen.h"
#include "LevelScreen.h"

SnakesGameManager::SnakesGameManager()
    : m_currentScreen(NULL)
{
	//subscribe to messages
	theSwitchboard.SubscribeTo(this, "StartGame");
    theSwitchboard.SubscribeTo(this, "ShowMenu");
    
	// We must set the sound callback method.  Although, I'm wondering if we should
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);
    
    //Show the Mainmenu first before doing anything
    showMenu();
}

SnakesGameManager::~SnakesGameManager()
{
    theSwitchboard.UnsubscribeFrom(this, "StartGame");
    theSwitchboard.UnsubscribeFrom(this, "ShowMenu");
}

void SnakesGameManager::showMenu()
{
    replaceScreen(new MenuScreen());
}

void SnakesGameManager::Update(float dt) { ; }
void SnakesGameManager::Render() { ; }

void SnakesGameManager::replaceScreen(SnakesScreen* screen)
{
    //While the next screen is going to be shown, the current screen will be dumped automatically
    if(m_currentScreen != NULL){
        m_currentScreen->Destroy();
        theWorld.Remove(m_currentScreen);
        delete m_currentScreen;
    }
    
    m_currentScreen = screen;
    theWorld.Add(m_currentScreen, kBackgroundLayer);
}

void SnakesGameManager::startLevel(int lvl_number)
{
    //TODO: do some level-loading procedure, now there is only one static level supported
    
    switch(lvl_number){
        default: replaceScreen(new LevelScreen());
    }
}

void SnakesGameManager::SoundEnded(AngelSoundHandle sound)
{	
	// Detect sounds that have ended here.
}

void SnakesGameManager::ReceiveMessage(Message* message)
{
    if(message->GetMessageName() == "StartGame")
	{
		startLevel(1);
	}
    else if(message->GetMessageName() == "ShowMenu"){
        showMenu();
    }
}
