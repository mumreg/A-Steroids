//
//  Layer.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Layer__
#define __A_Steroids__Layer__

#include <iostream>
#include "Node.h"

class Layer : public Node {
public:
    Layer();
    
    void addChild(Node *object);
    virtual void render();
    virtual void update(float dt);
private:
    std::vector<Node *> _childs;
};

#endif /* defined(__A_Steroids__Layer__) */
