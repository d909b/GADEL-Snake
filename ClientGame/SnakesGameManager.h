/**
 *  SnakesGameManager.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include <vector>

class SnakesScreen : public Renderable
{
public:
	virtual ~SnakesScreen() {;}
    
	virtual void Start();
	virtual void Stop(); //calls remove on all m_objects and deletes them
	virtual void Update(float dt);
	virtual void Render();
    
protected:
	std::vector<Renderable*> m_objects;
};

#define theGameManager SnakesGameManager::GetInstance()

/**
* @class SnakesGameManager
*
* @description Implementation of class SnakesGameManager.
*/
class SnakesGameManager : public GameManager
{
public:
    static SnakesGameManager& GetInstance();
	
	SnakesScreen* GetCurrentScreen();
	
	virtual void Render();
    
	virtual void SoundEnded(AngelSoundHandle sound);
    
	virtual void ReceiveMessage(Message* message);
protected:
    SnakesGameManager();
    static SnakesGameManager* s_gameManager;
private:
    void showMenu();
    void startGame();
    void showHighscore();
    
    SnakesScreen* m_currentScreen;
    SnakesScreen* m_menuScreen;
    SnakesScreen* m_gameScreen;
    SnakesScreen* m_highscoreScreen;
};
