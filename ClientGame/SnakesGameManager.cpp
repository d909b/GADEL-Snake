/**
 *  SnakesGameManager.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "SnakesGameManager.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "HighscoreScreen.h"

void
SnakesScreen::Start()
{}

void
SnakesScreen::Stop()
{
	std::vector<Renderable*>::iterator it = m_objects.begin();
	while(m_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it
		//  can mess with the pathfinding regeneration.
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if (pa != NULL)
		{
			if (pa->GetBody() != NULL)
			{
				pa->GetBody()->SetUserData(NULL);
				theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
				pa->ResetBody();
			}
		}
		(*it)->Destroy();
		it++;
	}
	m_objects.clear();
}

void
SnakesScreen::Update(float dt)
{}

void
SnakesScreen::Render()
{}

SnakesGameManager* SnakesGameManager::s_gameManager = NULL;

SnakesGameManager::SnakesGameManager()
{
	//subscribe to messages
	theSwitchboard.SubscribeTo(this, "StartGame");
    theSwitchboard.SubscribeTo(this, "ShowMenu");
	
    //Initialize Screens
    m_currentScreen = NULL;
    m_menuScreen = NULL;
    m_gameScreen = NULL;
    
    showMenu();
    
	
	// We must set the sound callback method.  Although, I'm wondering if we should
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);
}

SnakesGameManager&
SnakesGameManager::GetInstance()
{
	if (SnakesGameManager::s_gameManager == NULL)
	{
        SnakesGameManager::s_gameManager = new SnakesGameManager();
	}
	return *SnakesGameManager::s_gameManager;
}

SnakesScreen*
SnakesGameManager::GetCurrentScreen()
{
	return m_currentScreen;
}

void
SnakesGameManager::ReceiveMessage(Message* message)
{
    if(message->GetMessageName() == "StartGame")
	{
		startGame();
	}
    else if(message->GetMessageName() == "ShowMenu"){
        showMenu();
    }
}

void
SnakesGameManager::startGame()
{
    theWorld.Remove(m_currentScreen);
    m_gameScreen = new GameScreen();
    
    m_currentScreen->Stop();
    delete m_currentScreen;
    
    m_currentScreen = m_gameScreen;
    theWorld.Add(m_gameScreen);
    m_gameScreen->Start();
}

void
SnakesGameManager::showMenu()
{
    theWorld.Remove(m_currentScreen);
    if(m_currentScreen != NULL){
        m_currentScreen->Stop();
        delete m_currentScreen;
    }
    
    m_menuScreen = new MenuScreen;
    m_currentScreen = m_menuScreen;
    theWorld.Add(m_menuScreen);
    m_menuScreen->Start();
}

void
SnakesGameManager::Render()
{
	;
}

void
SnakesGameManager::SoundEnded(AngelSoundHandle sound)
{	
	// Detect sounds that have ended here.
}
