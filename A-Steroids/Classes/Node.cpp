//
//  Node.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 17.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Node.h"


using namespace std;

Node::Node()
{
    
}

void Node::render()
{
    if (!_isVisble) {
        return;
    }
    
    vector<Node *>::iterator it = children.begin();
    for (; it != children.end(); ++it) {
        (*it)->render();
    }
}

void Node::setVisible(bool flag)
{
    _isVisble = flag;
}

void Node::setPosition(const APoint &position)
{
    _position = position;
}

const APoint& Node::getPosition()
{
    return _position;
}

void Node::setRotation(const float angle)
{
    _angle = angle;
}

const float Node::getRotation()
{
    return _angle;
}

void Node::setShaderProgram(const char *programName)
{
//TODO:ShaderCache
//    _shaderProgram = new ShaderProgram(programName);
}

Node::~Node()
{
    
}