//
//  StartScene.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "StartScene.h"

StartScene::StartScene()
{
    winSize = getWinSize();

    startButton = new Sprite("start_label.png");
    startButton->setPosition({winSize.width/2, winSize.height/2});
    addChild(startButton);

    isGameRunning = false;
    
    gameScene = new GameScene();
    addChild(gameScene);
    
    setTouchEnabled(true);
    addToTouchDispatcher();
}

void StartScene::gameOver()
{
    startButton->setTexture("game_over_label.png");
    startButton->setPosition({ winSize.width/2, winSize.height/2 });
    startButton->setVisible(true);

    isGameRunning = false;
    setTouchEnabled(true);
}

void StartScene::touchesBegan(ASet *set)
{
    ARect bBox = startButton->getBoundingBox();
    
    for (int i = 0; i < set->getSize(); i++) {
        APoint *point = set->getObjectAtIndex(i);
        
        if (rectContainsPoint(&bBox, point)) {
            startTouched = true;
        }
    }
}

void StartScene::touchesEnded(ASet *set)
{
    ARect bBox = startButton->getBoundingBox();
    for (int i = 0; i < set->getSize(); i++) {
        APoint *point = set->getObjectAtIndex(i);
        
        if (rectContainsPoint(&bBox, point) && startTouched) {
            setTouchEnabled(false);
            startButton->setVisible(false);
            isGameRunning = true;
            gameScene->initGame();
            gameScene->start();
        }
    }
}
