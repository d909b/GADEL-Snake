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

FoodGenerator::FoodGenerator(Grid* grid) :
    m_currentFood(NULL),
    m_grid(grid)
{    
	theSwitchboard.SubscribeTo(this, "FoodConsumed");
}

void
FoodGenerator::Update(float dt)
{
    if(m_currentFood == NULL)
    {
        generateFood();
    }
}

void
FoodGenerator::ReceiveMessage(Message* m)
{
	if(m->GetMessageName() == "FoodConsumed")
    {
        generateFood();
    }
}

void
FoodGenerator::generateFood()
{
    if(m_currentFood != NULL)
    {
        m_grid->RemoveActor(m_currentFood);
        theWorld.Remove(m_currentFood);
    }
    
    Vector2 gridSize = m_grid->GetSize();
    
    Vector2 pos(MathUtil::RandomInt(gridSize.X),
                MathUtil::RandomInt(gridSize.Y));
    
    m_currentFood = new Food(m_grid->GridToWorldSpace(pos));
    m_grid->AddActor(m_currentFood);
    theWorld.Add(m_currentFood);
}