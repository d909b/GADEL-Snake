/**
 *  FoodGenerator.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "FoodGenerator.h"
#include "Grid.h"
#include "Food.h"
#include "Powerup.h"
#include "PowerupGenerator.h"

FoodGenerator::FoodGenerator(Grid* grid) :
    m_currentFood(NULL),
    m_currentPowerup(NULL),
    m_grid(grid)
{    
	theSwitchboard.SubscribeTo(this, "FoodConsumed");
    theSwitchboard.SubscribeTo(this, "PowerupConsumed");
}

FoodGenerator::~FoodGenerator()
{
    if(m_currentFood != NULL)
    {
        m_currentFood->Destroy();
    }
    
    if(m_currentPowerup != NULL){
        m_currentPowerup->Destroy();
    }
    
    theSwitchboard.UnsubscribeFrom(this, "FoodConsumed");
    theSwitchboard.UnsubscribeFrom(this, "PowerupConsumed");
}

void
FoodGenerator::Update(float dt)
{
    if(m_currentFood == NULL)
    {
        generateFood();
    }
    
    if(m_currentPowerup != NULL)
    {
        //Decrease TTL of the powerup and remove it if < 0
        m_currentPowerup->decreaseTTL(dt * 1000);
        
        //If the TTL exceeded, the object will be removed and destroyed completely
        if(m_currentPowerup->isTTLexceeded())
        {
            m_grid->RemoveActor(m_currentPowerup);
            m_currentPowerup->Destroy();
            m_currentPowerup = NULL;
        }
    }
}

void
FoodGenerator::ReceiveMessage(Message* m)
{
	if(m->GetMessageName() == "FoodConsumed")
    {
        generateFood();
        
        //Eventually spawn a powerup
        if(m_currentPowerup == NULL){
            int random = (rand() % 100) + 1; //Random number between 0 and 100
            if(random >= 60){
                generatePowerUp();
            }
        }
        
    }
    
    if(m->GetMessageName() == "PowerupConsumed")
    {        
        /* Remove but do not destroy the powerup, so it just doesn't show up
           on the grid*/
        m_grid->RemoveActor(m_currentPowerup);
        m_currentPowerup = NULL;
    }
}

void
FoodGenerator::generateFood()
{
    if(m_currentFood != NULL)
    {
        m_grid->RemoveActor(m_currentFood);
        m_currentFood->Destroy();
    }
    
    Vector2 pos = generatePosition();
    
    //Add normal food
    m_currentFood = new Food(m_grid->GridToWorldSpace(pos));
    m_grid->AddActor(m_currentFood);
    theWorld.Add(m_currentFood);
}

void FoodGenerator::generatePowerUp()
{
    if(m_currentPowerup != NULL)
    {
        m_grid->RemoveActor(m_currentPowerup);
        m_currentPowerup->Destroy();
    }
    
    PowerupType type = static_cast<PowerupType>(rand() % _LAST);
    Vector2 pos = generatePosition();
    
    //Add powerup with random type and TTL of 10 seconds
    m_currentPowerup = PowerupGenerator::produce(type, m_grid->GridToWorldSpace(pos), 10000);
    m_grid->AddActor(m_currentPowerup);
    theWorld.Add(m_currentPowerup);
}

Vector2 FoodGenerator::generatePosition()
{
    Vector2 gridSize = m_grid->GetSize();
    
    Vector2 pos(MathUtil::RandomInt(gridSize.X),
                MathUtil::RandomInt(gridSize.Y));
    
    while(m_grid->isCellOccupied(pos.X, pos.Y))
    {
        pos = Vector2(MathUtil::RandomInt(gridSize.X),
                      MathUtil::RandomInt(gridSize.Y));
    }
    
    return pos;
}