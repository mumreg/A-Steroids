//
//  Sprite.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Sprite.h"

#define kShaderTextureAndColor "Texture_and_color"

Sprite::Sprite(const char *fileName)
{
    
}

void Sprite::render()
{
    setShaderProgram(kShaderTextureAndColor);
}