//
//  Stone.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Stone.h"
#include "BaseEngine.h"

#define MIN_VERTS   4
#define MAX_VERTS   8

Stone::Stone(const APoint &poistion) : Node()
{
    _winSize = getWinSize();
    maxSize = _winSize.width/4;
    minSize = _winSize.width/8;
    
    _vertsN = MIN_VERTS + (rand() % (MAX_VERTS - MIN_VERTS));
    _verts = new APoint[_vertsN];
    for (int i = 0; i < _vertsN; i++) {
        _verts[i].x = (rand() % (int)(maxSize - minSize));
        _verts[i].y = (rand() % (int)(maxSize - minSize));
    }
    
    
}

int Stone::direction(APoint a, APoint b, APoint c)
{
    return (b.x - a.x)*(c.y - b.y)*(b.y - a.y)*(c.x - b.x);
}

void Stone::render()
{
    
}

void Stone::update(float dt)
{
    
}

Stone::~Stone()
{
    delete [] _verts;
}
