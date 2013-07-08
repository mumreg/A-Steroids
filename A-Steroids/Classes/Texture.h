//
//  Texture.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
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
    Texture(const char *data, int width, int height);
    Texture(Image *image);
    GLuint getName();
    
    const ASize getSize();
    
private:
    void initWithData(const char *data, int width, int height);
    GLuint _name;
    ASize _size;
};

#endif /* defined(__A_Steroids__Texture__) */
