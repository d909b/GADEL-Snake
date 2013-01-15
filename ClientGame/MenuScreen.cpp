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
    //Handle Subscriptions
    theSwitchboard.SubscribeTo(this, "EnterPressed");
    
    //Create GUI
    m_messageSent = false;
    
    m_start = new TextActor("standard", "Hit [Enter] to start the game...");
	m_start->SetPosition(MathUtil::ScreenToWorld(170.f, 500.f));
	m_start->SetColor(1.f, 1.f, 1.f);
    
    //Create background
    m_background = new Actor();
    m_background->SetSprite("Resources/Images/menu/title_screen.png");
    m_background->SetPosition(0.f, 0.f);
    m_background->SetSize(Vector2(theCamera.GetWorldMaxVertex().X*2, theCamera.GetWorldMaxVertex().Y*2));
    
    addRenderable(m_background, kBackgroundLayer);
    addRenderable(m_start, kDefaultLayer);
}

MenuScreen::~MenuScreen()
{
    theSwitchboard.UnsubscribeFrom(this, "EnterPressed");
}

void MenuScreen::Update(float dt) { ; }
void MenuScreen::Render() { ; }

void MenuScreen::ReceiveMessage(Message* m)
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
