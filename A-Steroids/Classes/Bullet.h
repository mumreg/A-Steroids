//
//  Bullet.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Bullet__
#define __A_Steroids__Bullet__

#include <iostream>
#include "BaseEngine.h"
#include "Body.h"

class Bullet : public Sprite {
public:
    Bullet(const char *fileName) : Sprite(fileName) {}
    virtual void callback();
};

#endif /* defined(__A_Steroids__Bullet__) */
