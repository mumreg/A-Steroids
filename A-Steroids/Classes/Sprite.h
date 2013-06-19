//
//  Sprite.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Sprite__
#define __A_Steroids__Sprite__

#include <iostream>
#include "Node.h"
#include "Texture.h"

class Sprite : public Node {
public:
    Sprite(const char *fileName);
    
    virtual void render();
private:
    Texture *texture;
};

#endif /* defined(__A_Steroids__Sprite__) */
