//
//  Layer.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Layer.h"

using namespace std;

Layer::Layer()
{
    
}

void Layer::addChild(Node *object)
{
    _childs.push_back(object);
}

void Layer::render()
{
    vector<Node *>::iterator it = _childs.begin();
    for (; it != _childs.end(); ++it) {
        (*it)->render();
    }
}

void Layer::update()
{
    vector<Node *>::iterator it = _childs.begin();
    for (; it != _childs.end(); ++it) {
        (*it)->update();
    }
}
