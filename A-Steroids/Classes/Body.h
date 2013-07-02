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
    BodyTypeTriagle = 0,
    BodyTypePolygon
};

class Body {
public:
    Body(APoint *verts, int vertsNumber, BodyType type, Sprite *sprite);
    
    void setVelocity(const APoint velocity);
    const APoint getVelocity();
    
    void setAccel(const APoint accel);
    const APoint getAccel();
    
    Sprite *getSprite();
    
    void setCollisionCallback(void (*callback)(void));
    void callCollisionCallback();
    
private:
    Sprite *_sprite;
    APoint *_verts;
    int _bodyType;
    
    APoint _velocity;
    APoint _accel;
    
    void (*_callback)(void);
};

#endif /* defined(__A_Steroids__Body__) */
