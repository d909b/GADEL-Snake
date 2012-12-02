/**
 *  Grid.h
 *  ClientGame
 *
 *  Created by patrick on 11/27/12.
 *
 */

#pragma once

#include <stdint.h>
#include <vector>

/**
* @class Grid
*
* @description Implementation of class Grid.
*/
class Grid
{
public:
	Grid(uint32_t width, uint32_t height);
    ~Grid();
    
    void LoadBackground(int layer);
    void Update(float dt);
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void SetIntermediatePosition(Actor* actor, Vector2 position);
    Vector2 GetIntermediatePosition(Actor* actor) const;
    Vector2 WorldSpaceToGrid(Vector2 pos) const;
    Vector2 GridToWorldSpace(Vector2 pos) const;
    Vector2 GetSize() const;
private:    
    uint32_t m_width, m_height;
    std::vector<Actor*> m_actors;
    
    typedef std::map<Actor*, Vector2> positionMapType;
    positionMapType m_intermediatePositions;
    
    typedef std::set<Actor*>** gridType;
    gridType m_collisionGrid;
};