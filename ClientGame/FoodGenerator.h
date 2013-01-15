/**
 *  FoodGenerator.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

class Powerup;
class Food;
class Grid;

/**
* @class FoodGenerator
*
* @description Implementation of class FoodGenerator.
*/
class FoodGenerator : public MessageListener
{
public:
    FoodGenerator(Grid* grid);
    ~FoodGenerator();
	void Update(float dt);
    virtual void ReceiveMessage(Message* m);
private:
    void generateFood();
    void generatePowerUp();
    Vector2 generatePosition();
    
    Food* m_currentFood;
    Powerup* m_currentPowerup;
    Grid* m_grid;
    
};