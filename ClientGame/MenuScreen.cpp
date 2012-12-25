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
    theSwitchboard.SubscribeTo(this, "EnterPressed");
}

MenuScreen::~MenuScreen()
{
    theSwitchboard.UnsubscribeFrom(this, "EnterPressed");
}

void
MenuScreen::Start()
{    
    m_messageSent = false;
    
    RegisterFont("Resources/Fonts/slkscrb.ttf", 30, "standard");
    RegisterFont("Resources/Fonts/slkscrb.ttf", 50.f, "game_over");
    
    m_start = new TextActor("standard", "Hit [Enter] to start the game...");
	m_start->SetPosition(MathUtil::ScreenToWorld(170.f, 500.f));
	m_start->SetColor(1.f, 1.f, 1.f);
    
    
    m_background = new Actor();
    m_background->SetSprite("Resources/Images/menu/title_screen.png");
    m_background->SetPosition(0.f, 0.f);
    m_background->SetSize(Vector2(theCamera.GetWorldMaxVertex().X*2, theCamera.GetWorldMaxVertex().Y*2));
    
    theWorld.Add(m_background, 0);
    theWorld.Add(m_start, 1);
    
    m_objects.push_back(m_start);
    m_objects.push_back(m_background);
}

void
MenuScreen::ReceiveMessage(Message* m)
{
    if(m->GetMessageName() == "EnterPressed")
    {
        if(!m_messageSent)
        {
            m_messageSent = true;
            theSwitchboard.Broadcast(new Message("StartGame"));
        }
    }
}
