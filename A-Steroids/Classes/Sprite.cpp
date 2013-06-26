//
//  Sprite.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Sprite.h"
#include <math.h>

const AVertex Vertices[] = {
    {{0.5, -0.5, 0.01}, {1, 1, 1, 1}, {1, 1}},
    {{0.5, 0.5, 0.01}, {1, 1, 1, 1}, {1, 0}},
    {{-0.5, 0.5, 0.01}, {1, 1, 1, 1}, {0, 0}},
    {{-0.5, -0.5, 0.01}, {1, 1, 1, 1}, {0, 1}},
};

const GLubyte Indices[] = {
    1, 0, 2, 3
};

Sprite::Sprite(const char *fileName)
{
    Image *image = new Image(fileName);
    _texture = new Texture(image);
    delete image;
    
    for (int i = 0; i < 4; i++) {
        _vertices[i] = Vertices[i];
    }
    
    eval();
    setShaderProgram(kShaderTextureAndColor);
    getShaderProgram()->use();
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    _matLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kShaderMVUniform);
    _projLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kShaderProjectUniform);
    
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
    
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glUniformMatrix4fv(_projLocation, 1, 0, _projection);
    glUniformMatrix4fv(_matLocation, 1, 0, _mv);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    ASize winSize = {1024, 768};
    glViewport(0, 0, winSize.width, winSize.height);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->getName());
    glUniform1i(_textureLocation, 0);

    glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), 0);
    glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(AVertex), (GLvoid*) (sizeof(float) * 3));
    glVertexAttribPointer(_texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(AVertex), (GLvoid*) (sizeof(float) * 7));
    
    glDrawElements(GL_TRIANGLE_STRIP, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);
}

void Sprite::eval()
{
    float angle = getRotation();
    
    //_projection
    float h = 4.0f * 768.0f / 1024.0f;
    float left = -2;
    float right = 2;
    float bottom = -h/2;
    float top = h/2;
    float near = 4;
    float far = 10;
    
    _projection[0]  = (2.0 * near) / (right - left);
	_projection[1]  = 0.0;
	_projection[2]  = 0.0;
	_projection[3] = 0.0;
	
	_projection[4]  = 0.0;
	_projection[5]  = (2.0 * near) / (top - bottom);
	_projection[6]  = 0.0;
	_projection[7] = 0.0;
	
	_projection[8]  = (right + left) / (right - left);
	_projection[9]  = (top + bottom) / (top - bottom);
	_projection[10] = -(far + near) / (far - near);
	_projection[11] = -1.0;
	
	_projection[12]  = 0.0;
	_projection[13]  = 0.0;
	_projection[14] = -(2.0 * far * near) / (far - near);
	_projection[15] = 0.0;
    
    //model view
    float mv[16] = { cosf(angle), sinf(angle), 0, 0,
        -sinf(angle), cosf(angle), 0, 0,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f};
    
    for (int i = 0; i < 16; i++) {
        _mv[i] = mv[i];
    }
}

Sprite::~Sprite()
{
    
}