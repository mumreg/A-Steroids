//
//  World.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 02.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include <math.h>
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

void World::removeBody(Body *body, bool cleanup)
{
    vector<Body *>::iterator it = find(_bodies.begin(), _bodies.end(), body);
    
    Body *bodyPtr = (*it);
    if (cleanup) {
        delete bodyPtr;
    }
    
    _bodies.erase(it);
}

void World::removeAll(bool cleanup)
{
    if (cleanup) {
        vector<Body *>::iterator it = _bodies.begin();
        for (; it != _bodies.end(); ++it) {
            Body *bodyPtr = (*it);
            delete bodyPtr;
        }
    }
    
    _bodies.clear();
}

void World::calcWorld(float dt)
{
    vector<Body *>::iterator it = _bodies.begin();

    //check for collisions
    for (; it != _bodies.end(); ++it) {
        Body *body1 = (*it);
        if (body1->getNode()->isVisible()) {
            if (body1->getBodyType() == BodyTypeTriangle || body1->getBodyType() == BodyTypeRectangle) {
                
                vector<Body *>::iterator it2 = _bodies.begin();
                for (; it2 != _bodies.end(); ++it2) {
                    Body *body2 = (*it2);
                    if (body2->getNode()->isVisible())
                    {
                        if (body1 != body2 && body2->getBodyType() == BodyTypePolygon) {
                            if (checkCollision(body1, body2)) {
                                body1->callCollisionCallback();
                                body2->callCollisionCallback();
                            }
                        }
                    }
                }
            }
        }
    }
    
    //calc speed
    it = _bodies.begin();
    for (; it != _bodies.end(); ++it) {
        Body *body = (*it);
        
        APoint velocity = body->getVelocity();
        APoint accel = body->getAccel();
        float damp = body->getDamp();
        
        accel = { accel.x*damp, accel.y*damp };
        velocity = { (velocity.x + accel.x)*damp, (velocity.y + accel.y)*damp };
        
        body->setVelocity(velocity);
        body->setAccel(accel);
        
        Node *sprite = body->getNode();
        APoint currentPos = sprite->getPosition();
        APoint newPos = {currentPos.x + velocity.x, currentPos.y + velocity.y};
        sprite->setPosition(newPos);
        
        float angle = body->getRotation() + body->getdAngle();
        sprite->setRotation(angle);
        body->setRotation(angle);
        
    }
}

void World::projectPolygon(APoint *verts, int vertsN, APoint axis, APoint offset, float *min, float *max)
{
    APoint firstPoint = { verts[0].x + offset.x, verts[0].y + offset.y };
    float _min = scalarMult(firstPoint, axis);
    float _max = _min;
    
    for (int i = 1; i < vertsN; i++) {
        APoint point = { verts[i].x + offset.x, verts[i].y + offset.y };
        float product = scalarMult(point, axis);
        if (product < _min) {
            _min = product;
        }
        if (product > _max) {
            _max = product;
        }
    }
    
    *min = _min;
    *max = _max;
}

float World::distance(float minA, float maxA, float minB, float maxB)
{
    if (minA < minB) {
        return minB - maxA;
    } else {
        return minA - maxB;
    }
}

void World::offsetPosition(APoint *position, Body *body)
{
    Node *body_sprite = (Node *)body->getNode();
    ASize body_size = body_sprite->getBoundingBox().size;
    
    position->x -= body_size.width/2;
    position->y -= body_size.height/2;
}

//body1 - triangle or rect
//body2 - polygon (i.e. stone)
bool World::checkCollision(Body *body1, Body *body2)
{
    APoint *body1_verts = body1->getVerts();
    APoint *body2_verts = body2->getVerts();
    
    APoint pos1 = body1->getNode()->getPosition();
    APoint pos2 = body2->getNode()->getPosition();
    
    offsetPosition(&pos1, body1);
    offsetPosition(&pos2, body2);
    
    int vertsN1 = body1->getVertsNumber();
    int vertsN2 = body2->getVertsNumber();
    
    APoint edge, p1, p2;
    for (int i = 0; i < vertsN1 + vertsN2; i++) {
        if (i < vertsN1) {
            p1 = { body1_verts[i].x + pos1.x, body1_verts[i].y + pos1.y };
            p2 = { body1_verts[(i + 1) % vertsN1].x + pos1.x, body1_verts[(i + 1) % vertsN1].y + pos1.y };
            edge = { p2.x - p1.x, p2.y - p1.y };
        }
        else {
            p1 = { body2_verts[i - vertsN1].x + pos2.x, body2_verts[i - vertsN1].y + pos2.y };
            p2 = { body2_verts[(i - vertsN1 + 1) % vertsN2].x + pos2.x, body2_verts[(i - vertsN1 + 1) % vertsN2].y + pos2.y};
            edge = { p2.x - p1.x, p2.y - p1.y };
        }
        
        APoint axis = normalize({ -edge.y, edge.x });

        float minA = 0, maxA = 0;
        float minB = 0, maxB = 0;
        projectPolygon(body1_verts, vertsN1, axis, pos1, &minA, &maxA);
        projectPolygon(body2_verts, vertsN2, axis, pos2, &minB, &maxB);
        
        if (distance(minA, maxA, minB, maxB) > 0) {
            return false;
        }
    }
    
    return true;
}