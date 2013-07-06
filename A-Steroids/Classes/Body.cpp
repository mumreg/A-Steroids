//
//  Body.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 02.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Body.h"

#define PTM_RATIO   10.0f

Body::Body(const APoint *verts, int vertsNumber, BodyType type, Node *node)
{
    _node = node;
    _verts = new APoint[vertsNumber];
    
    for (int i = 0; i < vertsNumber; i++) {
        _verts[i] = verts[i];
    }
    
    _vertsN = vertsNumber;
    _callback = NULL;
    
    _bodyType = type;
    _velocity = {0, 0};
    _accel = {0, 0};
    _rotation = 0;
    _damp = 1.0f;
}

APoint *Body::getVerts()
{
    return _verts;
}

int Body::getVertsNumber()
{
    return _vertsN;
}

int Body::getBodyType()
{
    return _bodyType;
}

void Body::setDamp(const float damp)
{
    _damp = damp;
}

float Body::getDamp()
{
    return _damp;
}

Node *Body::getNode()
{
    return _node;
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
    _node->callback();
}
