//
//  World.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 02.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__World__
#define __A_Steroids__World__

#include <iostream>
#include <vector>

#include "Body.h"
#include "Utils.h"

class World {
public:
    World(ARect screeRect);
    
    void addBody(Body *body, APoint position);
    void calcWorld(float dt);
private:
    bool checkForDelete(APoint position);
    bool checkCollision(Body *body1, Body *body2);
    void projectPolygon(APoint *verts, int vertsN, APoint axis, APoint offset, float *min, float *max);
    float distance(float minA, float maxA, float minB, float maxB);
    
    std::vector<Body *> _bodies;
    ARect _screenRect;
};

#endif /* defined(__A_Steroids__World__) */
