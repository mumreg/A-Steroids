//
//  StartScene.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 30.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__StartScene__
#define __A_Steroids__StartScene__

#include <iostream>
#include "BaseEngine.h"
#include "GameScene.h"

class StartScene : public Layer {
public:
    StartScene();
    
    virtual void touchesBegan(ASet *set);
    virtual void touchesEnded(ASet *set);
    
private:
    GameScene *gameScene;
    Sprite *startButton;
    ASize winSize;
    bool startTouched;
    bool isGameRunning;
};

#endif /* defined(__A_Steroids__StartScene__) */
