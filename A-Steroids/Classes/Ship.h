//
//  Ship.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Ship__
#define __A_Steroids__Ship__

#include <iostream>
#include "BaseEngine.h"

class Ship : public Sprite {
public:
    Ship(const char *fileName, APoint position);
};

#endif /* defined(__A_Steroids__Ship__) */
