/**
 *  MenuScreen.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "MenuScreen.h"

MenuScreen::MenuScreen()
{
    ;
}

void
MenuScreen::Start()
{
    m_isStartGame = true;
    
    m_start = new TextActor("Console", "Start Game");
	m_start->SetPosition(MathUtil::ScreenToWorld(theCamera.GetWindowWidth() / 2 - 50, theCamera.GetWindowHeight() / 2 - 30));
	m_start->SetColor(1.f, 0.f, 0.f);
    
    m_highscore = new TextActor("Console", "Highscore");
	m_highscore->SetPosition(MathUtil::ScreenToWorld(theCamera.GetWindowWidth() / 2 - 45, theCamera.GetWindowHeight() / 2 + 30));
	m_highscore->SetColor(1.f, 0.f, 0.f);
    
    theWorld.Add(m_start);
    theWorld.Add(m_highscore);
    
    m_objects.push_back(m_start);
    m_objects.push_back(m_highscore);
}

void
MenuScreen::Update(float dt)
{
    if(theInput.IsKeyDown(GLFW_KEY_ENTER))
    {
        if(m_isStartGame)
        {
            theSwitchboard.Broadcast(new Message("StartGame"));
        }
        else
        {
            theSwitchboard.Broadcast(new Message("ShowHighscore"));
        }
    }
    else if(theInput.IsKeyDown(GLFW_KEY_DOWN))
    {
        m_isStartGame = !m_isStartGame;
    }
    else if(theInput.IsKeyDown(GLFW_KEY_UP))
    {
        m_isStartGame = !m_isStartGame;
    }
}
