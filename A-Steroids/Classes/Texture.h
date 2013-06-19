//
//  Texture.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 19.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Texture__
#define __A_Steroids__Texture__

#include <iostream>
#include <OpenGLES/ES2/gl.h>

#include "Image.h"
#include "datatypes.h"

class Texture {
public:
    Texture(const char *data, ARect &rect);
    Texture(Image *image);
    GLuint getName();
private:
    GLuint _name;
};

#endif /* defined(__A_Steroids__Texture__) */
