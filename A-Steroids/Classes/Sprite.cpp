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
    
    setAnchorPoint({ 0.5f, 0.5f });
    updatePosition();
    eval();
    
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
    if (!isVisible())
        return;
    
    setShaderProgram(kShaderTextureAndColor);
    getShaderProgram()->use();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(0, 0, _winSize.width, _winSize.height);
    
    glUniformMatrix4fv(_mvLocation, 1, 0, _modelView.glMatrix());
    
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

ARect Sprite::boundingBox()
{
    APoint position = getPosition();
    ASize texSize = _texture->getSize();
    
    return {position.x - texSize.width/2, position.y - texSize.height/2, texSize.width, texSize.height};
}

void Sprite::setPosition(const APoint &position)
{
    Node::setPosition(position);
    eval();
}

void Sprite::setPosition(float x, float y)
{
    setPosition({x, y});
}

void Sprite::setRotation(const float rotation)
{
    Node::setRotation(rotation);
    eval();
}

void Sprite::updatePosition()
{
    APoint position = {0, 0};
    
    float dx = 2.0f/_winSize.width;
    float dy = 2.0f/_winSize.height;
    
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
    APoint position = getPosition();
    
    float dx = 2.0f/_winSize.width;
    float dy = 2.0f/_winSize.height;
    
    matrix4 translate;
    translate.setIdentity();
    
    float *translateArr = translate.glMatrix();
    translateArr[12] = -1.0f + position.x*dx ;
    translateArr[13] = -1.0f + position.y*dy;
    translateArr[14] = 0.0f;
    
    float angle = getRotation()*DegreesToRadiansFactor;

    matrix4 rotate;
    rotate.setIdentity();
    
    float *rotateArr = rotate.glMatrix();
    rotateArr[0] = cosf(angle);
    rotateArr[1] = sinf(angle);
    rotateArr[4] = -sinf(angle);
    rotateArr[5] = cosf(angle);
    
    _modelView = translate * rotate;
}

Sprite::~Sprite()
{
    
}