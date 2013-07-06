//
//  Node.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 17.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Node__
#define __A_Steroids__Node__

#include <iostream>
#include <vector>
#include "ShadersCache.h"
#include "datatypes.h"
#include "TouchProtocol.h"
#include "matrx4.h"

#define Z_POS       0.00

class Node : public TouchProtocol {
public:
    Node();
    virtual ~Node();
    virtual void render();
    virtual void update(float dt) {}

    virtual void setVisible(bool flag);
    virtual bool isVisible();
    
    virtual void setPosition(const APoint &position);
    virtual const APoint& getPosition();
    
    virtual void setAnchorPoint(const APoint &anchorPoint);
    virtual const APoint& getAnchorPoint();
    
    virtual void setRotation(const float angle);
    virtual const float getRotation();
    
    virtual void callback();
    
    void setShaderProgram(const char *programName);
    ShaderProgram *getShaderProgram();
    
    virtual void setTouchEnabled(bool touchEnabled);
    bool isTouchEnabled();
    
    virtual void touchesBegan(ASet *set) {}
    virtual void touchesMoved(ASet *set) {}
    virtual void touchesEnded(ASet *set) {}
    
    virtual void addToTouchDispatcher();
    
private:
    ShaderProgram *_shaderProgram;
    
    bool _isVisble;
    APoint _position;
    APoint _anchorPoint;
    float _angle;
    bool _touchEnabled;
};

#endif /* defined(__A_Steroids__Node__) */
