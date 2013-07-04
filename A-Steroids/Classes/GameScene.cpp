//
//  GameScene.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "GameScene.h"
#include <math.h>

#define SHIP_DAMP    0.99f

GameScene::GameScene()
{
    isGamePlaying = false;
    
    _winSize = getWinSize();
    
    _ship = new Ship("ship.png", {_winSize.width/2, _winSize.height/2});
    addChild(_ship);
    
    _fireButton = new Sprite("fire_button.png");
    _fireButton->setPosition({_winSize.width - _fireButton->boundingBox().size.width/2,
                             _fireButton->boundingBox().size.height/2});
    addChild(_fireButton);
    
    _joystick = new Joystick();
    addChild(_joystick);
    
    addPhysics();
    
    addToTouchDispatcher();
}

void GameScene::addPhysics()
{
    _world = new World({0, 0, _winSize.width, _winSize.height});
    
    APoint shipVerts[] = {{10.0f, 20.0f}, {20.0f, 30.0f}, {40.0f, 50.0f}};
    shipBody = new Body(shipVerts, 3, BodyTypeTriagle, _ship);
    shipBody->setDamp(SHIP_DAMP);
    _world->addBody(shipBody, _ship->getPosition());
    _joystick->setBody(shipBody);
}

void GameScene::fireBullet()
{
    float angle = _ship->getRotation()*DegreesToRadiansFactor;
    
    float xpos = _ship->getPosition().x + _ship->boundingBox().size.width/2*cosf(angle);
    float ypos = _ship->getPosition().y + _ship->boundingBox().size.width/2*cosf(90*DegreesToRadiansFactor - angle);
    
    Sprite *bullet = new Sprite("bullet.png");
    
    float xoffset = bullet->boundingBox().size.width/2*cosf(angle);
    float yoffset = bullet->boundingBox().size.width/2*cosf(90*DegreesToRadiansFactor - angle);
    
    bullet->setPosition({xpos + xoffset, ypos + yoffset});
    bullet->setRotation(_ship->getRotation());
    
    APoint bulletVerts[] = {{10.0f, 20.0f}, {20.0f, 30.0f}, {40.0f, 50.0f}, {50, 60.0f}};
    Body *bulletBody = new Body(bulletVerts, 4, BodyTypeRectangle, bullet);
    
    bulletBody->setRotation(bullet->getRotation());
    bulletBody->setVelocity({bullet->getPosition().x - _ship->getPosition().x,
                             bullet->getPosition().y - _ship->getPosition().y});
    
    _world->addBody(bulletBody, bullet->getPosition());
    
    addChild(bullet);
}

void GameScene::touchesBegan(ASet *set)
{
    ARect fireRect = _fireButton->boundingBox();
    
    for (int i = 0; i < set->getSize(); i++) {
        APoint *p = set->getObjectAtIndex(i);
        
        if (rectContainsPoint(&fireRect, p)) {
            fireBullet();
        }
    }
}

void GameScene::touchesEnded(ASet *set)
{
    
}

void GameScene::touchesMoved(ASet *set)
{
    
}

void GameScene::start()
{
    setTouchEnabled(true);
    _joystick->setTouchEnabled(true);
    isGamePlaying = true;
}

void GameScene::stop()
{
    setTouchEnabled(false);
    _joystick->setTouchEnabled(false);
    isGamePlaying = false;
}

void GameScene::update(float dt)
{
    if (isGamePlaying) {
        _world->calcWorld(dt);
        _joystick->update(dt);
    }
}

GameScene::~GameScene()
{
    delete _ship;
    delete _joystick;
    delete _fireButton;
    delete _world;
}
