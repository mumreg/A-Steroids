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

class Node {
public:
    Node();
    virtual ~Node();
    virtual void render();

    virtual void setVisible(bool flag);
    
    virtual void setPosition(const APoint &position);
    virtual const APoint& getPosition();
    
    virtual void setRotation(const float angle);
    virtual const float getRotation();
    
    void setShaderProgram(const char *programName);
    ShaderProgram *getShaderProgram();
    
private:
    ShaderProgram *_shaderProgram;
    std::vector<Node *> children;
    
    bool _isVisble;
    APoint _position;
    float _angle;
};

#endif /* defined(__A_Steroids__Node__) */
