//
//  Joystick.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Joystick.h"
#include <math.h>

#define DAMP        0.95f
#define PTM_RATIO   10.0f

Joystick::Joystick()
{
    staticCircle = new Sprite("static_circle.png");
    staticCircle->setPosition({staticCircle->boundingBox().size.width/2,
                                staticCircle->boundingBox().size.height/2});
    addChild(staticCircle);
    
    movingCircle = new Sprite("moving_circle.png");
    movingCircle->setPosition(staticCircle->getPosition());
    addChild(movingCircle);
    
    addToTouchDispatcher();
    
    isTouched = false;
}

void Joystick::setBody(Body *body)
{
    _body = body;
}

void Joystick::update(float dt)
{
    if (isTouchEnabled() && isTouched) {
        APoint center = staticCircle->getPosition();
        APoint dp = {(movingCircle->getPosition().x - center.x)/PTM_RATIO,
                        (movingCircle->getPosition().y - center.y)/PTM_RATIO};
        
        float len1 = movingCircle->getPosition().y - center.y;
        float len2 = vecLength({movingCircle->getPosition().x - center.x,
                                movingCircle->getPosition().y - center.y});
        float angle = (asinf(len1/len2))/DegreesToRadiansFactor;
        
        if (movingCircle->getPosition().x - center.x < 0) {
            angle = -angle - 180;
        }
        
        _body->setRotation(angle);
        _body->setVelocity(dp);
    }
}

void Joystick::touchesBegan(ASet *set)
{
    ARect movingRect = movingCircle->boundingBox();
    
    for (int i = 0; i < set->getSize(); i++) {
        APoint *p = set->getObjectAtIndex(i);
        if (rectContainsPoint(&movingRect, p)) {
            isTouched = true;
            prevPoint = *p;
        }
    }
}

void Joystick::touchesMoved(ASet *set)
{
    ARect movingRect = movingCircle->boundingBox();
    
    for (int i = 0; i < set->getSize(); i++) {
        APoint *p = set->getObjectAtIndex(i);
        if (rectContainsPoint(&movingRect, p) && isTouched) {
            restrictPoint(p);
            movingCircle->setPosition({p->x*DAMP, p->y*DAMP});
        }
    }
}

void Joystick::touchesEnded(ASet *set)
{
//    isTouched = false;
}

void Joystick::restrictPoint(APoint *p)
{
    APoint center = staticCircle->getPosition();
    float r = staticCircle->boundingBox().size.width/4;
    
    if (p->x > center.x + r) {
        p->x = center.x + r;
    }
    if (p->x < center.x - r) {
        p->x = center.x - r;
    }
    if (p->y > center.y + r) {
        p->y = center.y + r;
    }
    if (p->y < center.y - r) {
        p->y = center.y - r;
    }
}

ARect Joystick::boundingBox()
{
    return movingCircle->boundingBox();
}

Joystick::~Joystick()
{
    delete staticCircle;
    delete movingCircle;
}
