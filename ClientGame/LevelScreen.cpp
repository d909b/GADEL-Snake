/**
 *  LevelScreen.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "LevelScreen.h"
#include <sstream>
#include <iomanip>

#include "MovingObstacle.h"
#include "CirclingObstacle.h"


//TESTINCLUDE
#include "FastPowerup.h"


LevelScreen::LevelScreen() :
    m_grid(32,
           24),
    m_foodGenerator(&m_grid),
    m_highscoreCounter(0)
{
    //TODO: CREATE SOME KIND OF LEVEL-WRAPPER, WHICH ADDS THE ACTORS IN THE GRID
    
    theSwitchboard.SubscribeTo(this, "FoodConsumed");
    theSwitchboard.SubscribeTo(this, "PowerupConsumed");
    theSwitchboard.SubscribeTo(this, "ObstacleHit");
    theSwitchboard.SubscribeTo(this, "HidePopup");
    
    m_snake = new Snake(&m_grid);
    
    //TESTCODE
    //m_snake->addPowerup(new FastPowerup(Vector2(0,0), 10000));
    //m_snake->addPowerup(new FastPowerup(Vector2(0,0), 10000));
    //m_snake->addPowerup(new FastPowerup(Vector2(0,0), 10000));
    //TESTCODE END
    
    //Generate obstacles to dodge
    MovingObstacle* obstacle = new MovingObstacle(Vector2(6, 0), Vector2(0,1), 1.0, 100.0, "Resources/Images/obstacles/spikecube.png", m_snake);
    CirclingObstacle* circleObstacle = new CirclingObstacle(Vector2(0,0), 1.0, 8.0, "Resources/Images/obstacles/spikecube.png", m_snake);
    
    //Generate UI elements
    m_statusbox = new StatusBox(MathUtil::ScreenToWorld(100, 20), m_snake, 10);
    
    m_highscore = new TextActor("Console", "0000");
    m_highscore->SetPosition(MathUtil::ScreenToWorld(5, 25));
    m_highscore->SetColor(1, 1, 1);
    
    m_popupText = new TextActor("popup", "", TXT_Center);
    
    //Prepare the grid
    m_grid.LoadBackground(kBackgroundLayer);
    m_grid.AddActor(m_snake);
    
    //Add the renderables to the world and m_objects vector
    addRenderable(obstacle, kObstacleLayer);
    addRenderable(circleObstacle, kObstacleLayer);
    addRenderable(m_snake, kSnakeHeadLayer);
    addRenderable(m_highscore, kUILayer);
    addRenderable(m_popupText, kUILayer);
    addRenderable(m_statusbox, kUILayer);
}

LevelScreen::~LevelScreen()
{
    theSwitchboard.UnsubscribeFrom(this, "FoodConsumed");
    theSwitchboard.UnsubscribeFrom(this, "PowerupConsumed");
    theSwitchboard.UnsubscribeFrom(this, "ObstacleHit");
    theSwitchboard.UnsubscribeFrom(this, "HidePopup");
}

void LevelScreen::Update(float dt)
{
    m_foodGenerator.Update(dt);
}

void LevelScreen::Render()
{
    /** 
     * Call after position updates so the grid can snap actors to the cell boundaries.
     * This has to be in Render() because it must be called AFTER all actors' position updates.
     */
    //m_grid.Update(0.f);
}

void LevelScreen::ReceiveMessage(Message* m)
{
    if(m->GetMessageName() == "FoodConsumed")
    {
        std::stringstream ss;
        
        m_highscoreCounter += m_snake->getPointMultiplicator();
        
        ss << std::setfill('0') << std::setw(4) << m_highscoreCounter;
        
        m_highscore->SetDisplayString(ss.str());
    }
    else if(m->GetMessageName() == "PowerupConsumed")
    {
        std::stringstream ss;
        m_highscoreCounter += m_snake->getPointMultiplicator();
        ss << std::setfill('0') << std::setw(4) << m_highscoreCounter;
        
        Powerup* powerup = static_cast<Powerup*>(m->GetSender());
        
        if(powerup != NULL)
        {
            m_popupText->SetColor(1.f, 1.f, 1.f);
            m_popupText->SetDisplayString(powerup->getDescription());
            m_popupText->ChangeColorTo(Color(1.0,0.0,0.0), 5.0, true, "HidePopup");
            theWorld.Add(m_popupText, kUILayer);
        }
    }
    else if(m->GetMessageName() == "HidePopup")
    {
        theWorld.Remove(m_popupText);
    }
    else if(m->GetMessageName() == "EnterPressed")
    {
        theSwitchboard.UnsubscribeFrom(this, "EnterPressed");
        theSwitchboard.Broadcast(new Message("ShowMenu"));
    }
    else if(m->GetMessageName() == "ObstacleHit")
    {
        theWorld.Remove(m_popupText);
        m_snake->stop();
                
        TextActor* gameOver = new TextActor("popup", "GAME OVER");
        gameOver->SetPosition(-4.8f, 4.0f);
        gameOver->SetColor(1.f, 1.f, 1.f);
        
        TextActor* hitEnterText = new TextActor("standard", "Hit [Enter] to get back to menu...");
        hitEnterText->SetPosition(-8.8f, 0.0f);
        hitEnterText->SetColor(1.f, 1.f, 1.f);
        
        addRenderable(gameOver, kUILayer);
        addRenderable(hitEnterText, kUILayer);
        
        theSwitchboard.SubscribeTo(this, "EnterPressed");
    }
}
