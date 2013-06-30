//
//  StartScene.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 30.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "StartScene.h"

StartScene::StartScene()
{
    winSize = getWinSize();
    
    startButton = new Sprite("item_powerup_fish.png");
    startButton->setPosition({winSize.width/2, winSize.height/2});
    addChild(startButton);
}

