//
//  TouchDispatcher.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "TouchDispatcher.h"
#include "datatypes.h"
#include "ASet.h"
#include "Utils.h"

using namespace std;

TouchDispatcher* TouchDispatcher::sharedInstance()
{
    static TouchDispatcher *pDispatcher = NULL;
    if (pDispatcher == NULL) {
        pDispatcher = new TouchDispatcher();
    }
    
    return pDispatcher;
}

TouchDispatcher::TouchDispatcher()
{
    ASize winSize = getWinSize();
    _screenRect = ARect({0, winSize.height, winSize.width, winSize.height});
}

void TouchDispatcher::addObject(Node *object)
{
    _objects.push_back(object);
}

void TouchDispatcher::removeObject(Node *object)
{
    vector<Node *>::iterator it = _objects.begin();
    
    int pos = -1;
    int count = 0;
    
    for (; it != _objects.end(); ++it) {
        if ((*it) == object) {
            pos = count;
            break;
        }
        count++;
    }
    
    if (pos != -1) {
        _objects.erase(_objects.begin() + pos);
    }
}

void TouchDispatcher::touchesBegan(int num, int *ids, float *xs, float *ys)
{
    ASet set;
    
    for (int i = 0; i < num; i++) {
        APoint *point = new APoint;
        point->x = xs[i];
        point->y = _screenRect.origin.y - ys[i];
        
        set.addObject(point);
    }
    
    vector<Node *>::iterator it = _objects.begin();
    for (; it != _objects.end(); ++it) {
        Node *pNode = (*it);
        if (pNode->isTouchEnabled()) {
            pNode->touchesBegan(&set);
        }
    }
    set.removeAllObjects();
}

void TouchDispatcher::touchesMoved(int num, int *ids, float *xs, float *ys)
{
    ASet set;
    
    for (int i = 0; i < num; i++) {
        APoint *point = new APoint;
        point->x = xs[i];
        point->y = _screenRect.origin.y - ys[i];
        
        set.addObject(point);
    }
    
    vector<Node *>::iterator it = _objects.begin();
    for (; it != _objects.end(); ++it) {
        Node *pNode = (*it);
        if (pNode->isTouchEnabled()) {
            pNode->touchesMoved(&set);
        }
    }
    set.removeAllObjects();
}

void TouchDispatcher::touchesEnded(int num, int *ids, float *xs, float *ys)
{
    ASet set;
    
    for (int i = 0; i < num; i++) {
        APoint *point = new APoint;
        point->x = xs[i];
        point->y = _screenRect.origin.y - ys[i];
        
        set.addObject(point);
    }
    
    vector<Node *>::iterator it = _objects.begin();
    for (; it != _objects.end(); ++it) {
        Node *pNode = (*it);
        if (pNode->isTouchEnabled()) {
            pNode->touchesEnded(&set);
        }
    }
   set.removeAllObjects();
}
