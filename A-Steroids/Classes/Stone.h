//
//  Stone.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Stone__
#define __A_Steroids__Stone__

#include <iostream>
#include "BaseEngine.h"

class Stone : public Node {
public:
    Stone(const APoint &position);
    ~Stone();
    
    virtual void render();
    virtual void update(float dt);
private:
    int direction(APoint a, APoint b, APoint c);
    
    APoint _position;
    ASize _winSize;
    float minSize;
    float maxSize;
    
    APoint *_verts;
    int _vertsN;
};

#endif /* defined(__A_Steroids__Stone__) */
