//
//  Layer.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Layer.h"

using namespace std;

Layer::Layer()
{
    
}

void Layer::removeChild(Node *object, bool cleanup)
{
    vector<Node *>::iterator it = find(_childs.begin(), _childs.end(), object);
    
    Node *node = (*it);
    if (cleanup) {
        delete node;
    }
    
    _childs.erase(it);
    
}

void Layer::addChild(Node *object)
{
    object->setParent(this);
    _childs.push_back(object);
}

void Layer::render()
{
    vector<Node *>::reverse_iterator it = _childs.rbegin();
    for (; it != _childs.rend(); ++it) {
        (*it)->render();
    }
}

void Layer::update(float dt)
{
    vector<Node *>::reverse_iterator it = _childs.rbegin();
    for (; it != _childs.rend(); ++it) {
        (*it)->update(dt);
    }
}

vector<Node *> *Layer::children()
{
    return &_childs;
}