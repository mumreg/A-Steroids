//
//  Joystick.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Joystick__
#define __A_Steroids__Joystick__

#include <iostream>
#include "BaseEngine.h"

class Joystick : public Layer {
public:
    Joystick();
    ~Joystick();
private:
    Sprite *staticCircle;
    Sprite *movingCircle;
};

#endif /* defined(__A_Steroids__Joystick__) */
