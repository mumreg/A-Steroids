//
//  Ship.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Ship.h"
#include "GameScene.h"

Ship::Ship(const char *fileName, APoint position) : Sprite(fileName)
{
    _winSize = getWinSize();
    setPosition(position);
}

void Ship::callback()
{
    setVisible(false);
    GameScene *parent = (GameScene *)getParent();
    parent->gameOver();
}

void Ship::setPosition(const APoint &position)
{
    ASize size = getBoundingBox().size;
    APoint newPos = position;
    
    if (position.x > _winSize.width - size.width/2) {
        newPos.x = _winSize.width - size.width/2;
    }
    if (position.x < size.width/2) {
        newPos.x = size.width/2;
    }
    if (position.y > _winSize.height - size.height/2) {
        newPos.y = _winSize.height - size.height/2;
    }
    if (position.y < size.height/2) {
        newPos.y = size.height/2;
    }
    
    Sprite::setPosition(newPos);
}
