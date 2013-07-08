//
//  Texture.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Texture.h"

Texture::Texture(const char *data, int width, int height)
{
    initWithData(data, width, height);
}

void Texture::initWithData(const char *data, int width, int height)
{
    glGenTextures(1, &_name);
    glBindTexture(GL_TEXTURE_2D, _name);
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,(GLubyte *)data);
    
    _size.width = width;
    _size.height = height;
    
    delete data;
}

Texture::Texture(Image *image)
{
    initWithData((const char *)image->getImageData(), image->getImageSize().width, image->getImageSize().height);
}

const ASize Texture::getSize()
{
    return _size;
}

GLuint Texture::getName()
{
    return _name;
}
