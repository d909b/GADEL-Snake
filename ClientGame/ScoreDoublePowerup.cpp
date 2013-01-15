//
//  ScoreDoublePowerup.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 13.01.13.
//
//

#include "ScoreDoublePowerup.h"

ScoreDoublePowerup::ScoreDoublePowerup(Vector2 position, unsigned int ttl_milliseconds)
: Powerup(position, ttl_milliseconds, "Double Score", "Resources/Images/Food/double_powerup.png"), m_original_Multiplicator(1)
{
    ;
}

void ScoreDoublePowerup::applyEffect(Snake *snake)
{
    m_original_Multiplicator = snake->getPointMultiplicator();
    snake->setPointMultiplicator(m_original_Multiplicator * 2);
}

void ScoreDoublePowerup::undoEffect(Snake *snake)
{
    snake->setPointMultiplicator(m_original_Multiplicator);
}
