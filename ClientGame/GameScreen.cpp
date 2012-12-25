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
    m_grid(32,
           24),
    m_foodGenerator(&m_grid),
    m_highscoreCounter(0)
{
    theSwitchboard.SubscribeTo(this, "FoodConsumed");
    theSwitchboard.SubscribeTo(this, "ObstacleHit");
}

GameScreen::~GameScreen()
{
    theSwitchboard.UnsubscribeFrom(this, "FoodConsumed");
    theSwitchboard.UnsubscribeFrom(this, "ObstacleHit");
}

void
GameScreen::Start()
{
    m_snake = new Snake(&m_grid);
    m_highscore = new TextActor("Console", "0000");
    m_highscore->SetPosition(MathUtil::ScreenToWorld(5, 25));
    m_highscore->SetColor(1, 1, 1);
    
    m_grid.LoadBackground(kBackgroundLayer);
    
    theWorld.Add(m_highscore, kHighscoreLayer);
    m_grid.AddActor(m_snake);
    theWorld.Add(m_snake, kSnakeHeadLayer);
    m_objects.push_back(m_snake);
    m_objects.push_back(m_highscore);
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
    else if(m->GetMessageName() == "EnterPressed")
    {
        theSwitchboard.UnsubscribeFrom(this, "EnterPressed");
        theSwitchboard.Broadcast(new Message("ShowMenu"));
    }
    else if(m->GetMessageName() == "ObstacleHit")
    {
        m_snake->stop();
        
        TextActor* gameOver = new TextActor("game_over", "GAME OVER");
        gameOver->SetPosition(-4.8f, 4.0f);
        gameOver->SetColor(1.f, 1.f, 1.f);
        
        TextActor* hitEnterText = new TextActor("standard", "Hit [Enter] to get back to menu...");
        hitEnterText->SetPosition(-8.8f, 0.0f);
        hitEnterText->SetColor(1.f, 1.f, 1.f);
        
        theWorld.Add(gameOver, kHighscoreLayer);
        m_objects.push_back(gameOver);
        theWorld.Add(hitEnterText, kHighscoreLayer);
        m_objects.push_back(hitEnterText);
        
        theSwitchboard.SubscribeTo(this, "EnterPressed");
    }
}
