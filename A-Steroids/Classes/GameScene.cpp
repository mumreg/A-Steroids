//
//  GameScene.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "GameScene.h"
#include <math.h>

using namespace std;

#define SHIP_DAMP       0.99f
#define SHIP_VERTS      {0, 0}, {0, 33.0f}, {64.0f, 33.0f/2}
#define SHIP_VERTS_N    3

#define BULLET_VERTS    {0.0f, 0.0f}, {0.0f, 15.0f}, {5.0f, 15.0f}, {5.0f, 0.0f}
#define BULLET_VERTS_N  4

#define MIN_STONES      6
#define MAX_STONES      8
#define STONE_DAMP      1.0f
#define STONE_VEL       100
#define STONE_VEL_DAMP  250.0f

GameScene::GameScene()
{
    isGamePlaying = false;
    
    _winSize = getWinSize();
    
    _fireButton = new Sprite("fire_button.png");
    _fireButton->setPosition({_winSize.width - _fireButton->getBoundingBox().size.width/2,
                             _fireButton->getBoundingBox().size.height/2});
    addChild(_fireButton);
    
    _joystick = new Joystick();
    addChild(_joystick);
    
    _ship = new Ship("ship.png", {_winSize.width/2, _winSize.height/2});
    addChild(_ship);
    
    addStones();
    addPhysics();
    
    addToTouchDispatcher();
}

void GameScene::addStones()
{
    srand(time(NULL));
    int stonesN = MIN_STONES + (rand() % (MAX_STONES - MIN_STONES));
    
    float xpos = 0, ypos = 0;
    
    for (int i = 0; i < 1; i++) {
        Stone *st = new Stone();
        
        if (i < stonesN/2) {
            xpos = rand() % (int)(_winSize.width/2 - _winSize.width/4);
            ypos = rand() % (int)(_winSize.height);
        }
        else {
            xpos = (_winSize.width/2 + _winSize.width/4) + (rand() % (int)(_winSize.width/2 - _winSize.width/4));
            ypos = rand() % (int)(_winSize.height);
        }
        
        st->setPosition({xpos, ypos});
        addChild(st);
        stones.push_back(st);
    }
}

void GameScene::addPhysics()
{
    _world = new World({0, 0, _winSize.width, _winSize.height});
    
    APoint shipVerts[] = {SHIP_VERTS};
    shipBody = new Body(shipVerts, SHIP_VERTS_N, BodyTypeTriangle, _ship);
    shipBody->setDamp(SHIP_DAMP);
    _world->addBody(shipBody, _ship->getPosition());
    
    vector<Node *>::iterator it = stones.begin();
    for (; it != stones.end(); ++it) {
        Stone *st = (Stone *)(*it);
        
        Body *stoneBody = new Body(st->getScreenVerts(), st->getVertsNumber(), BodyTypePolygon, st);
        
        float velX = -STONE_VEL/2 + (rand() % STONE_VEL);
        float velY = -STONE_VEL/2 + (rand() % STONE_VEL);
        
        stoneBody->setVelocity({velX/STONE_VEL_DAMP, velY/STONE_VEL_DAMP});
        stoneBody->setDamp(STONE_DAMP);
        
        _world->addBody(stoneBody, st->getPosition());
    }
    
    _joystick->setBody(shipBody);
}

void GameScene::fireBullet()
{
    float angle = _ship->getRotation()*DegreesToRadiansFactor;
    
    float xpos = _ship->getPosition().x + _ship->getBoundingBox().size.width/2*cosf(angle);
    float ypos = _ship->getPosition().y + _ship->getBoundingBox().size.width/2*cosf(90*DegreesToRadiansFactor - angle);
    
    Sprite *bullet = new Bullet("bullet.png");
    
    float xoffset = bullet->getBoundingBox().size.width/2*cosf(angle);
    float yoffset = bullet->getBoundingBox().size.width/2*cosf(90*DegreesToRadiansFactor - angle);
    
    bullet->setPosition({xpos + xoffset, ypos + yoffset});
    bullet->setRotation(_ship->getRotation());
    
    APoint bulletVerts[] = {BULLET_VERTS};
    Body *bulletBody = new Body(bulletVerts, BULLET_VERTS_N, BodyTypeRectangle, bullet);
    
    bulletBody->setRotation(bullet->getRotation());
    bulletBody->setVelocity({bullet->getPosition().x - _ship->getPosition().x,
                             bullet->getPosition().y - _ship->getPosition().y});
    
    _world->addBody(bulletBody, bullet->getPosition());
    
    addChild(bullet);
}

void GameScene::touchesBegan(ASet *set)
{
    ARect fireRect = _fireButton->getBoundingBox();
    
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
