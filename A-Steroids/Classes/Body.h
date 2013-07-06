//
//  Body.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 02.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Body__
#define __A_Steroids__Body__

#include <iostream>
#include "Sprite.h"

enum BodyType {
    BodyTypeTriangle = 0,
    BodyTypePolygon,
    BodyTypeRectangle
};

class Body {
public:
    Body(const APoint *verts, int vertsNumber, BodyType type, Node *node);
    ~Body();
    
    void setVelocity(const APoint velocity);
    const APoint getVelocity();
    
    void setAccel(const APoint accel);
    const APoint getAccel();
    
    void setRotation(const float angle);
    float getRotation();
    
    Node *getNode();
    
    void setCollisionCallback(void (*callback)(void));
    void callCollisionCallback();

    void setDamp(const float damp);
    float getDamp();
    
    int getBodyType();
    APoint *getVerts();
    int getVertsNumber();
    
private:
    Node *_node;
    APoint *_verts;
    int _vertsN;
    int _bodyType;
    
    APoint _velocity;
    APoint _accel;
    float _rotation;
    float _damp;
    
    void (*_callback)(void);
};

#endif /* defined(__A_Steroids__Body__) */
