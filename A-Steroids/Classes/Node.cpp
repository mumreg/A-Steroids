//
//  Node.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 17.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Node.h"
#include "Utils.h"
#include "TouchDispatcher.h"

using namespace std;

Node::Node()
{
    _angle = 0.0f;
    _position = {0, 0};
    _anchorPoint = {0, 0};
    _isVisble = true;
    _touchEnabled = false;
}

void Node::render()
{
    if (!_isVisble) {
        return;
    }
}

void Node::setAnchorPoint(const APoint &anchorPoint)
{
    _anchorPoint = anchorPoint;
}

const APoint& Node::getAnchorPoint()
{
    return _anchorPoint;
}

void Node::setVisible(bool flag)
{
    _isVisble = flag;
}

bool Node::isVisible()
{
    return _isVisble;
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

void Node::setTouchEnabled(bool touchEnabled)
{
    _touchEnabled = touchEnabled;
}

bool Node::isTouchEnabled()
{
    return _touchEnabled;
}

void Node::addToTouchDispatcher()
{
    TouchDispatcher::sharedInstance()->addObject(this);
}

void Node::setShaderProgram(const char *programName)
{
    _shaderProgram = ShadersCache::sharedInstance()->getProgram(programName);
}

void Node::setBoundingBox(ARect &rect)
{
    _boundingBox = rect;
}

ARect Node::getBoundingBox()
{
    return _boundingBox;
}

void Node::callback()
{}

ShaderProgram *Node::getShaderProgram()
{
    return _shaderProgram;
}

Node::~Node()
{
    //override me
}