/**
 *  GameScreen.cpp
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#include "GameScreen.h"

GameScreen::GameScreen() :
    m_grid(theCamera.GetWorldMaxVertex().X * 2, theCamera.GetWorldMaxVertex().Y * 2)
{
    ;
}

void
GameScreen::Start()
{
	m_snake = new Actor();
    m_snake->SetColor(0, 0, 0);
    m_snake->SetDrawShape(ADS_Square);
    m_snake->SetSize(1.);
    m_snake->SetPosition(0, 0);
    
    m_highscore = new TextActor("Console", "0000");
    m_highscore->SetPosition(MathUtil::ScreenToWorld(5, 25));
    m_highscore->SetColor(0, 0, 0);
    
    theWorld.Add(new GridActor());
    theWorld.Add(m_highscore);
    m_grid.AddActor(m_snake);
    theWorld.Add(m_snake);
    m_objects.push_back(m_snake);
}

void
GameScreen::Update(float dt)
{
    static const float kSnakeMovementSpeed = 10.f;
    static int lastDirection = GLFW_KEY_UP;
    
	if(theInput.IsKeyDown(GLFW_KEY_UP) ||
       theInput.IsKeyDown('w'))
    {
        lastDirection = GLFW_KEY_UP;
    }
    else if(theInput.IsKeyDown(GLFW_KEY_DOWN) ||
            theInput.IsKeyDown('s'))
    {
        lastDirection = GLFW_KEY_DOWN;
    }
    else if(theInput.IsKeyDown(GLFW_KEY_LEFT) ||
            theInput.IsKeyDown('a'))
    {
        lastDirection = GLFW_KEY_LEFT;
    }
    else if(theInput.IsKeyDown(GLFW_KEY_RIGHT) ||
            theInput.IsKeyDown('d'))
    {
        lastDirection = GLFW_KEY_RIGHT;
    }
    
    Vector2 pos = m_grid.GetIntermediatePosition(m_snake);
    
    switch(lastDirection)
    {
        case GLFW_KEY_UP:
            pos.Y += kSnakeMovementSpeed * dt;
            break;
        case GLFW_KEY_DOWN:
            pos.Y -= kSnakeMovementSpeed * dt;
            break;
        case GLFW_KEY_LEFT:
            pos.X -= kSnakeMovementSpeed * dt;
            break;
        case GLFW_KEY_RIGHT:
            pos.X += kSnakeMovementSpeed * dt;
            break;
    }
    
    m_grid.SetIntermediatePosition(m_snake, pos);
    
    /** Call after position updates so the grid can snap actors back to the cell boundaries. */
    m_grid.Update(dt);
}

