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
#include "Body.h"

class Joystick : public Layer {
public:
    Joystick();
    ~Joystick();
    
    void restrictPoint(APoint *p);
    void setBody(Body *body);
    
    virtual void touchesBegan(ASet *set);
    virtual void touchesMoved(ASet *set);
    virtual void touchesEnded(ASet *set);
    
    virtual void update(float dt);
    
    ARect boundingBox();
private:
    Sprite *staticCircle;
    Sprite *movingCircle;
    
    Body *_body;
    
    APoint prevPoint;
    bool isTouched;
};

#endif /* defined(__A_Steroids__Joystick__) */
