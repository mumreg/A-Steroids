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
    ~Sprite();
    
    virtual void render();
    virtual void setPosition(const APoint &position);
    virtual void setPosition(float x, float y);
    virtual void setRotation(const float rotation);
    
    virtual ARect getBoundingBox();
    
private:
    void eval();
    void updatePosition();
    
    Texture *_texture;
    GLuint _textureLocation;
    GLuint _colorLocation;
    GLuint _texCoordsLocation;
    GLuint _mvLocation;
//    GLuint _projLocation;
    GLuint _positionLocation;
    
    GLuint _vertexBuffer;
    GLuint _indexBuffer;

    AVertex _vertices[4];
    matrix4 _modelView;
//    float _projection[16];
    
    ASize _winSize;
};

#endif /* defined(__A_Steroids__Sprite__) */
