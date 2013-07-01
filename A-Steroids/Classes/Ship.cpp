//
//  Ship.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Ship.h"

Ship::Ship(const char *fileName, APoint position) : Sprite(fileName)
{
    setPosition(position);
}


