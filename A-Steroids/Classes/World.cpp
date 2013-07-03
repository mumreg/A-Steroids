//
//  World.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 02.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "World.h"

using namespace std;

World::World(ARect screenRect)
{
    _screenRect = screenRect;
}

void World::addBody(Body *body, APoint position)
{
    _bodies.push_back(body);
}

void World::calcWorld(float dt)
{
    //check for collisions
    
    //calc speed
    vector<Body *>::iterator it = _bodies.begin();
    for (; it != _bodies.end(); ++it) {
        Body *body = (*it);
        
        APoint velocity = body->getVelocity();
        APoint accel = body->getAccel();
        float damp = body->getDump();
        
        accel = {accel.x*damp, accel.y*damp};
        velocity = {(velocity.x + accel.x)*damp, (velocity.y + accel.y)*damp};
        
        body->setVelocity(velocity);
        body->setAccel(accel);
        
        Sprite *sprite = body->getSprite();
        APoint currentPos = sprite->getPosition();
        APoint newPos = {currentPos.x + velocity.x, currentPos.y + velocity.y};
        sprite->setPosition(newPos);
        sprite->setRotation(body->getRotation());
        
        checkForDelete(newPos);
    }
}


bool World::checkForDelete(APoint position)
{
    return false;
}