//
//  Sprite.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Sprite.h"
#include <math.h>
#include "Utils.h"

#define Z_POS   0.00
#define DEF_COLOR   1, 1, 1, 1

const GLubyte Indices[] = {
    1, 0, 2, 3
};

Sprite::Sprite(const char *fileName)
{
    Image *image = new Image(fileName);
    _texture = new Texture(image);
    delete image;
    
    _winSize = getWinSize();
    
    setPosition({_winSize.width/2, _winSize.height/2});
    
    eval();
    updatePosition();
    
    setShaderProgram(kShaderTextureAndColor);
    getShaderProgram()->use();
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    _mvLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kShaderMVUniform);
    
    _positionLocation = glGetAttribLocation(getShaderProgram()->getProgram(), kShaderPositionAttr);
    _colorLocation = glGetAttribLocation(getShaderProgram()->getProgram(), kShaderColorAttr);
    glEnableVertexAttribArray(_positionLocation);
    glEnableVertexAttribArray(_colorLocation);
    
    _texCoordsLocation = glGetAttribLocation(getShaderProgram()->getProgram(), kShaderTextureAttr);
    glEnableVertexAttribArray(_texCoordsLocation);
    _textureLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kShaderTextureUniform);
}

void Sprite::render()
{
    Node::render();
    
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glViewport(0, 0, _winSize.width, _winSize.height);
    
    glUniformMatrix4fv(_mvLocation, 1, 0, _mv);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->getName());
    glUniform1i(_textureLocation, 0);

    glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), 0);
    glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(AVertex), (GLvoid*) (sizeof(float) * 3));
    glVertexAttribPointer(_texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(AVertex), (GLvoid*) (sizeof(float) * 7));
    
    glDrawElements(GL_TRIANGLE_STRIP, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);
}

void Sprite::setPosition(const APoint &position)
{
    Node::setPosition(position);
    updatePosition();
}

void Sprite::updatePosition()
{
    APoint position = getPosition();
    
    position.x -= _winSize.width;
    position.y -= _winSize.height;
    
    float dx = 1.0f/_winSize.width;
    float dy = 1.0f/_winSize.height;
    
    ASize textureSize = _texture->getSize();
    
    float x1 = (position.x + textureSize.width/2)*dx;
    float y1 = (position.y - textureSize.height/2)*dy;
    
    float x2 = (position.x + textureSize.width/2)*dx;
    float y2 = (position.y + textureSize.height/2)*dy;
    
    float x3 = (position.x - textureSize.width/2)*dx;
    float y3 = (position.y + textureSize.height/2)*dy;
    
    float x4 = (position.x - textureSize.width/2)*dx;
    float y4 = (position.y - textureSize.height/2)*dy;
    
    _vertices[0] = {{x1, y1, Z_POS}, {DEF_COLOR}, {1, 1}};
    _vertices[1] = {{x2, y2, Z_POS}, {DEF_COLOR}, {1, 0}};
    _vertices[2] = {{x3, y3, Z_POS}, {DEF_COLOR}, {0, 0}};
    _vertices[3] = {{x4, y4, Z_POS}, {DEF_COLOR}, {0, 1}};
}

void Sprite::eval()
{
    float angle = 45.0f*DegreesToRadiansFactor;
    ASize texSize = _texture->getSize();
    
    //model view
    float mv[16] = {
        cosf(angle), sinf(angle), 0, texSize.width/2,
        -sinf(angle), cosf(angle), 0, texSize.height/2,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f
    };
    
    for (int i = 0; i < 16; i++) {
        _mv[i] = mv[i];
    }
}

Sprite::~Sprite()
{
    
}