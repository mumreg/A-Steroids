//
//  GameScene.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "GameScene.h"
#include "StartScene.h"
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
#define STONES_TIMEOUT  3.0f

GameScene::GameScene()
{
    isGamePlaying = false;
    _winSize = getWinSize();
    
    addControls();
    _ship = new Ship("ship.png", {_winSize.width/2, _winSize.height/2});
    addChild(_ship);
    addPhysics();
    
    addToTouchDispatcher();
}

void GameScene::addControls()
{
    _fireButton = new Sprite("fire_button.png");
    _fireButton->setPosition({_winSize.width - _fireButton->getBoundingBox().size.width/2,
        _fireButton->getBoundingBox().size.height/2});
    addChild(_fireButton);
    
    _joystick = new Joystick();
    addChild(_joystick);
}

void GameScene::resetShip()
{
    _ship->setPosition({ _winSize.width/2, _winSize.height/2 });
    _ship->setRotation(0);
    shipBody->setRotation(0);
    shipBody->setAccel({ 0, 0 });
    shipBody->setVelocity({ 0, 0 });
    _ship->setVisible(true);
}

void GameScene::initGame()
{
    if (stones.size() != 0) {
        removeAllStones();
    }
    
    _joystick->reset();
    resetShip();
    addStones();
}

void GameScene::removeAllStones()
{
    vector<Node *>::iterator it = stones.begin();
    for (; it != stones.end(); ++it) {
        Stone *stone = (Stone *)(*it);
        
        Body *body = stone->getBody();
        _world->removeBody(body, true);
        
        removeChild(stone, true);
    }
    stones.clear();
}

void GameScene::removeObject(Node *node)
{
    vector<Node *>::iterator it = find(stones.begin(), stones.end(), node);
    
    Node *obj = node;
    if (it != stones.end()) {
        obj = (*it);
    }
    
    Body *body = node->getBody();
    _world->removeBody(body, true);
    removeChild(obj, true);
    
    stones.erase(it);
}

void GameScene::addStone(Stone *stone)
{
    Body *stoneBody = stone->getBody();
    stoneBody->setDamp(STONE_DAMP);
    
    _world->addBody(stoneBody, stone->getPosition());
    
    addChild(stone);
    stones.push_back(stone);
}

void GameScene::addStones()
{
    srand(time(NULL));
    int stonesN = MIN_STONES + (rand() % (MAX_STONES - MIN_STONES));
    
    float xpos = 0, ypos = 0;
    
    for (int i = 0; i < stonesN; i++) {
        Stone *st = new Stone();
        
        xpos = _winSize.width/2;
        ypos = _winSize.height/2;
        if (i < stonesN/2) {
            xpos = rand() % (int)(_winSize.width/2 - _winSize.width/4);
            ypos = rand() % (int)(_winSize.height);
        }
        else {
            xpos = (_winSize.width/2 + _winSize.width/4) + (rand() % (int)(_winSize.width/2 - _winSize.width/4));
            ypos = rand() % (int)(_winSize.height);
        }
        
        st->setPosition({xpos, ypos});
        stones.push_back(st);
        
        Body *stoneBody = new Body(st->getScreenVerts(), st->getVertsNumber(), BodyTypePolygon, st);
        
        float velX = -STONE_VEL/2 + (rand() % STONE_VEL);
        float velY = -STONE_VEL/2 + (rand() % STONE_VEL);
        
        stoneBody->setVelocity({velX/STONE_VEL_DAMP, velY/STONE_VEL_DAMP});
        stoneBody->setDamp(STONE_DAMP);
        float angle = (-10 + (rand() % 20))/100.0f;
        stoneBody->setdAngle(angle);
        
        st->setBody(stoneBody);
        
        _world->addBody(stoneBody, st->getPosition());
        addChild(st);
    }
}

void GameScene::addPhysics()
{
    _world = new World({0, 0, _winSize.width, _winSize.height});
    
    APoint shipVerts[] = {SHIP_VERTS};
    shipBody = new Body(shipVerts, SHIP_VERTS_N, BodyTypeTriangle, _ship);
    shipBody->setDamp(SHIP_DAMP);
    _world->addBody(shipBody, _ship->getPosition());
    
    _joystick->setBody(shipBody);
}

void GameScene::fireBullet()
{
    float angle = _ship->getRotation()*DegreesToRadiansFactor;
    
    float xpos = _ship->getPosition().x + _ship->getBoundingBox().size.width/2*cosf(angle);
    float ypos = _ship->getPosition().y + _ship->getBoundingBox().size.width/2*cosf(90*DegreesToRadiansFactor - angle);
    
    Bullet *bullet = new Bullet("bullet.png");
    
    float xoffset = bullet->getBoundingBox().size.width/2*cosf(angle);
    float yoffset = bullet->getBoundingBox().size.width/2*cosf(90*DegreesToRadiansFactor - angle);
    
    bullet->setPosition({xpos + xoffset, ypos + yoffset});
    bullet->setRotation(_ship->getRotation());
    
    APoint bulletVerts[] = {BULLET_VERTS};
    Body *bulletBody = new Body(bulletVerts, BULLET_VERTS_N, BodyTypeRectangle, bullet);
    
    bulletBody->setRotation(bullet->getRotation());
    bulletBody->setVelocity({bullet->getPosition().x - _ship->getPosition().x,
                             bullet->getPosition().y - _ship->getPosition().y});
    
    bullet->setBody(bulletBody);
    _world->addBody(bulletBody, bullet->getPosition());
    
    stones.push_back(bullet);
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

void GameScene::gameOver()
{
    stop();
    StartScene *parent = (StartScene *)getParent();
    parent->gameOver();
}

void GameScene::stoneCallback(Stone *stone)
{
    if (!isGamePlaying) {
        return;
    }
    
    splitStone(stone);
}

void GameScene::splitStone(Stone *stone)
{
    if (stone->getHits() == 1) {
        stone->setVisible(false);
        toRemove.push_back(stone);
        return;
    }
    
    int vertsN = stone->getVertsNumber();
    const APoint *stoneVerts = stone->getScreenVerts();
    
    vector<APoint> newVerts;
    int i = 0;
    if (vertsN >= 4) {
        for (int i = 0; i < vertsN; i++) {
            newVerts.push_back(stoneVerts[i]);
        }
    }
    else {
        while (vertsN < 4) {
            APoint p1 = stoneVerts[i];
            APoint p2 = stoneVerts[(i + 1) % vertsN];
            
            APoint newPoint = { p1.x + (p2.x - p1.x)/2, p2.y + (p2.y - p1.y)/2 };
            
            newVerts.push_back(p1);
            newVerts.push_back(newPoint);
            newVerts.push_back(p2);
            vertsN++;
        }
    }
    
    int newStoneVertsN = vertsN/2 + 1;
    APoint *stoneVerts1 = new APoint[newStoneVertsN];
    APoint *stoneVerts2 = new APoint[newStoneVertsN];
    
    for (int i = 0; i < newStoneVertsN; i++) {
        stoneVerts1[i] = newVerts[i];
    }
    
    stoneVerts2[0] = newVerts[0];
    for (int i = 0; i < newStoneVertsN - 1; i++) {
        stoneVerts2[i + 1] = newVerts[(i + vertsN/2)];
    }
    
    Stone *stone1 = new Stone(stoneVerts1, newStoneVertsN, stone->getHits() - 1);
    Stone *stone2 = new Stone(stoneVerts2, newStoneVertsN, stone->getHits() - 1);
    
    APoint stonePos = stone->getPosition();
    float offset = 10;
    APoint stonePos1 = { stonePos.x - offset, stonePos.y - offset };
    APoint stonePos2 = { stonePos.x + offset, stonePos.y + offset };
    stone1->setPosition(stonePos1);
    stone2->setPosition(stonePos2);
    
    Body *stoneBody1 = new Body(stone->getScreenVerts(), stone->getVertsNumber(), BodyTypePolygon, stone1);
    Body *stoneBody2 = new Body(stone->getScreenVerts(), stone->getVertsNumber(), BodyTypePolygon, stone2);
    
    APoint stoneVel = stone->getBody()->getVelocity();
    int minVel = -1 + (rand() % 2);
    stoneBody1->setVelocity({ minVel + stoneVel.x*2*minVel, - 1 - stoneVel.y*2 });
    stoneBody2->setVelocity({ minVel + stoneVel.x*2*minVel, 1 + stoneVel.y*2 });
    
    stoneBody1->setdAngle(-stone->getBody()->getdAngle()*2);
    stoneBody2->setdAngle(stone->getBody()->getdAngle()*2);
    
    stone1->setBody(stoneBody1);
    stone2->setBody(stoneBody2);
    
    toRemove.push_back(stone);
    toAdd.push_back(stone1);
    toAdd.push_back(stone2);
}

void GameScene::update(float dt)
{
    if (isGamePlaying) {
        _world->calcWorld(dt);
        _joystick->update(dt);
        checkForDelete();
        checkForAdd(dt);
        
        if (toRemove.size() != 0) {
            vector<Node *>::iterator it = toRemove.begin();
            for (; it != toRemove.end(); ++it) {
                Node *node = (Node *)(*it);
                removeObject(node);
            }
            
            toRemove.clear();
        }
        
        if (toAdd.size() != 0) {
            vector<Node *>::iterator it = toAdd.begin();
            for (; it != toAdd.end(); ++it) {
                Stone *stone = (Stone *)(*it);
                addStone(stone);
            }
            toAdd.clear();
        }
    }
}

void GameScene::checkForAdd(float dt)
{
    static float timeout = 0;
    timeout += dt;
    
    if (timeout > STONES_TIMEOUT || stones.size() < MIN_STONES) {
        timeout = 0;
        int stonesN = 6 + (rand() % 4);
        
        for (int i = 0; i < stonesN; i++) {
            Stone *stone = new Stone();
            Body *stoneBody = new Body(stone->getScreenVerts(), stone->getVertsNumber(), BodyTypePolygon, stone);
            stone->setBody(stoneBody);
            
            float velX = rand() % STONE_VEL;
            float velY = rand() % STONE_VEL;
            
            int side = 1 + rand() % 4;
            switch (side) {
                case 1: //left
                {
                    stone->setPosition({ -stone->getBoundingBox().size.width, (float)(rand() % ((int)_winSize.height/2)) });
                    break;
                }
                case 2: //right
                {
                    stone->setPosition({ _winSize.width + stone->getBoundingBox().size.width, (float)(rand() % (int)_winSize.height/2) });
                    velX = -velX;
                    break;
                }
                case 3: //up
                {
                    stone->setPosition({ (float)(rand() % (int)_winSize.width), _winSize.height + stone->getBoundingBox().size.height/2 });
                    velY = -velY;
                    break;
                }
                case 4: //down
                {
                    stone->setPosition({ (float)(rand() % (int)_winSize.width), -stone->getBoundingBox().size.height/2 });
                    break;
                }
                    
                default:
                    break;
            }
            
            stoneBody->setVelocity({velX/STONE_VEL_DAMP, velY/STONE_VEL_DAMP});
            float angle = (-10 + (rand() % 20))/100.0f;
            stoneBody->setdAngle(angle);
            
            toAdd.push_back(stone);
        }
    }
}

void GameScene::checkForDelete()
{
    vector<Node *> *childs = this->children();
    vector<Node *>::iterator it = childs->begin();
    for (; it != childs->end(); ++it) {
        Node *child = (*it);
        APoint position = child->getPosition();
        
        if (outOfBounds(position)) {
            toRemove.push_back(child);
        }
    }
}

bool GameScene::outOfBounds(APoint &position)
{
    bool flag = false;
    if (position.x < -_winSize.width/2) {
        flag = true;
    }
    if (position.y < -_winSize.height/2) {
        flag = true;
    }
    if (position.x > _winSize.width*1.5f) {
        flag = true;
    }
    if (position.y > _winSize.height*1.5) {
        flag = true;
    }
    
    return flag;
}

GameScene::~GameScene()
{
    delete _ship;
    delete _joystick;
    delete _fireButton;
    delete _world;
}
