//
//  SnakesScreen.cpp
//  ClientGame
//
//  Created by Patrick Stapfer on 15.01.13.
//
//

#include "SnakesScreen.h"

SnakesScreen::~SnakesScreen()
{
    std::vector<Renderable*>::iterator it = m_objects.begin();
	while(m_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it
		//  can mess with the pathfinding regeneration.
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if (pa != NULL)
		{
			if (pa->GetBody() != NULL)
			{
				pa->GetBody()->SetUserData(NULL);
				theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
				pa->ResetBody();
			}
		}
		(*it)->Destroy();
		it++;
	}
    
    //After destroying each object, references are clear and are dropped from the collection
	m_objects.clear();
}

void SnakesScreen::Update(float dt) { ; }
void SnakesScreen::Render() { ; }

void SnakesScreen::addRenderable(Renderable* renderable)
{
    addRenderable(renderable, kDefaultLayer);
}

void SnakesScreen::addRenderable(Renderable* renderable, int layer)
{
    m_objects.push_back(renderable);
    theWorld.Add(renderable, layer);
}