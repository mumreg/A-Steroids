//
//  Joystick.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Joystick.h"

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
}

Joystick::~Joystick()
{
    delete staticCircle;
    delete movingCircle;
}
