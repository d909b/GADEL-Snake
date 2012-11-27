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
    theSwitchboard.SubscribeTo(this, "EnterPressed");
    theSwitchboard.SubscribeTo(this, "MenuMoveUp");
    theSwitchboard.SubscribeTo(this, "MenuMoveDown");
    
    m_isStartGame = true;
    m_messageSent = false;
    
    m_start = new TextActor("Console", "Start Game");
	m_start->SetPosition(MathUtil::ScreenToWorld(theCamera.GetWindowWidth() / 2 - 50,
                                                 theCamera.GetWindowHeight() / 2 - 30));
	m_start->SetColor(1.f, 0.f, 1.f);
    
    m_highscore = new TextActor("Console", "Highscore");
	m_highscore->SetPosition(MathUtil::ScreenToWorld(theCamera.GetWindowWidth() / 2 - 45,
                                                     theCamera.GetWindowHeight() / 2 + 30));
	m_highscore->SetColor(1.f, 0.f, 0.f);
    
    theWorld.Add(m_start);
    theWorld.Add(m_highscore);
    
    m_objects.push_back(m_start);
    m_objects.push_back(m_highscore);
}

void
MenuScreen::ReceiveMessage(Message* m)
{
    if(m->GetMessageName() == "EnterPressed")
    {
        if(m_isStartGame)
        {
            if(!m_messageSent)
            {
                m_messageSent = true;
                theSwitchboard.UnsubscribeFrom(this, "EnterPressed");
                theSwitchboard.UnsubscribeFrom(this, "MenuMoveUp");
                theSwitchboard.UnsubscribeFrom(this, "MenuMoveDown");
                theSwitchboard.Broadcast(new Message("StartGame"));
            }
        }
        else
        {
            if(!m_messageSent)
            {
                m_messageSent = true;
                theSwitchboard.UnsubscribeFrom(this, "EnterPressed");
                theSwitchboard.UnsubscribeFrom(this, "MenuMoveUp");
                theSwitchboard.UnsubscribeFrom(this, "MenuMoveDown");
                theSwitchboard.Broadcast(new Message("ShowHighscore"));
            }
        }
    }
    else if(m->GetMessageName() == "MenuMoveUp" || m->GetMessageName() == "MenuMoveDown")
    {
        m_isStartGame = !m_isStartGame;
        
        if(m_isStartGame)
        {
            m_start->SetColor(1.f, 0.f, 1.f);
            m_highscore->SetColor(1.f, 0.f, 0.f);
        }
        else
        {
            m_start->SetColor(1.f, 0.f, 0.f);
            m_highscore->SetColor(1.f, 0.f, 1.f);
        }
    }
}
