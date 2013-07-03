//
//  Body.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 02.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Body.h"

#define PTM_RATIO   10.0f

Body::Body(APoint *verts, int vertsNumber, BodyType type, Sprite *sprite)
{
    _sprite = sprite;
    _verts = new APoint[vertsNumber];
    
    for (int i = 0; i < vertsNumber; i++) {
        _verts[i] = verts[i];
    }
    
    _callback = NULL;
    
    _bodyType = type;
    _velocity = {0, 0};
    _accel = {0, 0};
    _rotation = 0;
    _damp = 1.0f;
}

void Body::setDamp(const float damp)
{
    _damp = damp;
}

float Body::getDump()
{
    return _damp;
}

Sprite *Body::getSprite()
{
    return _sprite;
}

void Body::setRotation(const float angle)
{
    _rotation = angle;
}

float Body::getRotation()
{
    return _rotation;
}

void Body::setVelocity(const APoint velocity)
{
    _velocity = velocity;
}

const APoint Body::getVelocity()
{
    return _velocity;
}

void Body::setAccel(const APoint accel)
{
    _accel = accel;
}

const APoint Body::getAccel()
{
    return _accel;
}

void Body::callCollisionCallback()
{
    if (_callback != NULL)
        _callback();
}
