//
//  GameScene.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "GameScene.h"

GameScene::GameScene()
{
    _winSize = getWinSize();
    
    _ship = new Ship("ship.png", {_winSize.width/2, _winSize.height/2});
    addChild(_ship);
    
    _fireButton = new Sprite("fire_button.png");
    _fireButton->setPosition({_winSize.width - _fireButton->boundingBox().size.width/2,
                             _fireButton->boundingBox().size.height/2});
    addChild(_fireButton);
    
    _joystick = new Joystick();
    addChild(_joystick);
    
    _world = new World();
    
    addToTouchDispatcher();
}

void GameScene::touchesBegan(ASet *set)
{
    ARect fireRect = _fireButton->boundingBox();
    
    for (int i = 0; i < set->getSize(); i++) {
        APoint *p = set->getObjectAtIndex(i);
        
        if (rectContainsPoint(&fireRect, p)) {
            
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
    }
}

GameScene::~GameScene()
{
    delete _ship;
    delete _joystick;
    delete _fireButton;
    delete _world;
}
