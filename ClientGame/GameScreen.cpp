/**
 *  GameScreen.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "GameScreen.h"
#include <sstream>
#include <iomanip>

#define kBackgroundLayer -1
#define kSnakeHeadLayer kBackgroundLayer + 2
#define kHighscoreLayer kSnakeHeadLayer + 1

GameScreen::GameScreen() :
    m_grid(theCamera.GetWorldMaxVertex().X * 2,
           theCamera.GetWorldMaxVertex().Y * 2),
    m_foodGenerator(&m_grid),
    m_highscoreCounter(0)
{
    theSwitchboard.SubscribeTo(this, "FoodConsumed");
}

void
GameScreen::Start()
{
    m_snake = new Snake(&m_grid);
    m_highscore = new TextActor("Console", "0000");
    m_highscore->SetPosition(MathUtil::ScreenToWorld(5, 25));
    m_highscore->SetColor(0, 0, 0);
    
    theWorld.Add(new GridActor());
    theWorld.Add(m_highscore, kHighscoreLayer);
    m_grid.AddActor(m_snake);
    theWorld.Add(m_snake, kSnakeHeadLayer);
    m_objects.push_back(m_snake);
}

void
GameScreen::Update(float dt)
{
    m_foodGenerator.Update(dt);
}

void
GameScreen::Render()
{
    /** 
     * Call after position updates so the grid can snap actors to the cell boundaries.
     * This has to be in Render() because it must be called AFTER all actors' position updates.
     */
    m_grid.Update(0.f);
}

void
GameScreen::ReceiveMessage(Message* m)
{
    if(m->GetMessageName() == "FoodConsumed")
    {
        std::stringstream ss;
        
        ss << std::setfill('0') << std::setw(4) << ++m_highscoreCounter;
        
        m_highscore->SetDisplayString(ss.str());
    }
}
