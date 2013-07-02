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

class World {
public:
    World();
    
    void addBody(Body *body, APoint position);
    void calcWorld(float dt);
private:
    std::vector<Body *> _bodies;
};

#endif /* defined(__A_Steroids__World__) */
