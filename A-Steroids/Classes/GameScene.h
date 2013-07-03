//
//  GameScene.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__GameScene__
#define __A_Steroids__GameScene__

#include <iostream>
#include "BaseEngine.h"

#include "Ship.h"
#include "Stone.h"
#include "Bullet.h"
#include "Joystick.h"
#include "World.h"

class GameScene : public Layer {
public:
    GameScene();
    ~GameScene();
    void start();
    void stop();
    
    void addPhysics();
    
    void fireBullet();
    
    virtual void touchesBegan(ASet *set);
    virtual void touchesEnded(ASet *set);
    virtual void touchesMoved(ASet *set);
    
    virtual void update(float dt);
    
private:
    Joystick *_joystick;
    Ship *_ship;
    Sprite *_fireButton;
    ASize _winSize;
    Body *shipBody;
    
    World *_world;
    
    bool isGamePlaying;
};

#endif /* defined(__A_Steroids__GameScene__) */
