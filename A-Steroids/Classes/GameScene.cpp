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
    
    _fireButton = new Sprite("fire_button.png");
    _fireButton->setPosition({_winSize.width - _fireButton->boundingBox().size.width,
                             _fireButton->boundingBox().size.height});
    addChild(_fireButton);
    
    _joystick = new Joystick();
    addChild(_joystick);
    
    addToTouchDispatcher();
}

void GameScene::touchesBegan(ASet *set)
{
    
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
}

void GameScene::stop()
{
    setTouchEnabled(false);
}

GameScene::~GameScene()
{
    delete _fireButton;
}
