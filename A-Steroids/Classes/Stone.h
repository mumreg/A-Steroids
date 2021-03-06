//
//  Stone.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Sprite1__
#define __A_Steroids__Sprite1__

#include <iostream>
#include "Node.h"
#include "Texture.h"
#include "Body.h"

#define MAX_VERTS   16
#define MIN_VERTS   10
#define MIN_ANGLES  5
#define MAX_HITS    2

class Stone : public Node {
public:
    Stone();
    Stone(APoint *verts, int vertsN, int hits);
    ~Stone();
    
    virtual void render();
    virtual void setPosition(const APoint &position);
    virtual void setPosition(float x, float y);
    virtual void setRotation(const float rotation);
    
    virtual void callback();
    virtual ARect getBoundingBox();
    
    void removeFromView();
    const APoint *getScreenVerts();
    int getVertsNumber();
    int getHits();
    
private:
    void eval();
    void updatePosition();
    int direction(APoint a, APoint b, APoint c);
    void generateVerts();
    void initStone(int hits);
    void makeVerts(APoint *verts, int vertsN);
    void setupDraw();

    GLuint _colorLocation;
    GLuint _mvLocation;
    GLuint _positionLocation;
    
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    
    AVertexColor _vertices[MAX_VERTS];
    APoint *_screenVerts;
    GLubyte Indices[MAX_VERTS*2];
    matrix4 _modelView;
    int _vertsN;
    float maxSize;
    int _hits;
    
    ASize _winSize;
};

#endif /* defined(__A_Steroids__Sprite__) */
