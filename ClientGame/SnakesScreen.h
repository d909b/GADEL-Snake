//
//  SnakesScreen.h
//  ClientGame
//
//  Created by Patrick Stapfer on 15.01.13.
//
//

#ifndef __ClientGame__SnakesScreen__
#define __ClientGame__SnakesScreen__

#include <iostream>
#include <vector>

#define kDefaultLayer 0
#define kBackgroundLayer kDefaultLayer -1
#define kObstacleLayer kDefaultLayer + 1
#define kSnakeHeadLayer kObstacleLayer + 1
#define kUILayer kSnakeHeadLayer + 1

class SnakesScreen : public Renderable
{
public:
    //Removes all m_objects and deletes them
	~SnakesScreen();
    
	virtual void Update(float dt);
	virtual void Render();
    
    //Drops the Renderable in the world and appends them to the m_objects list
    //Uses kDefaultLayer as layer default if not given
    void addRenderable(Renderable* renderable);
    void addRenderable(Renderable* renderable, int layer);
protected:
	std::vector<Renderable*> m_objects;
};

#endif /* defined(__ClientGame__SnakesScreen__) */
