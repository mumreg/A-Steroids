//
//  Stone.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include <math.h>
#include "Stone.h"
#include "Utils.h"
#include "GameScene.h"

using namespace std;

#define DEF_COLOR       164/255.0f, 164/255.0f, 164/255.0f, 1.0f
#define DCOLOR          40
#define STONE_MAX_SIZE  150

Stone::Stone()
{
    _winSize = getWinSize();
    setAnchorPoint( {0.5f, 0.5f} );
    _hits = MAX_HITS;
    
    generateVerts();
    setupDraw();
}

Stone::Stone(APoint *verts, int vertsN, int hits)
{
    _winSize = getWinSize();
    setAnchorPoint( {0.5f, 0.5f} );
    _hits = hits;
    
    float dx = 2.0f/_winSize.width;
    float dy = 2.0f/_winSize.height;
    
    AColor color = {DEF_COLOR};
    float dcolor = (-DCOLOR/2 + (rand() % DCOLOR))/255.0f;
    color.r += dcolor;
    color.g += dcolor;
    color.b += dcolor;
    
    APoint left = {0, 0};
    APoint right = left;
    APoint up = left;
    APoint down = left;
    
    for (int i = 0; i < vertsN; i++) {
        APoint point = verts[i];
        
        if (point.x < left.x) {
            left = point;
        }
        if (point.x > right.x) {
            right = point;
        }
        if (point.y < down.y) {
            down = point;
        }
        if (point.y > up.y) {
            up = point;
        }
    }
    
    float width = right.x - left.x;
    float height = up.y - down.y;
    
    ARect _boundingBox = { left.x, down.y, width - left.x, height - down.y };
    setBoundingBox(_boundingBox);
    
    APoint anchorPoint = getAnchorPoint();
    
    _screenVerts = new APoint[vertsN];
    
    for (int i = 0; i < vertsN; i++) {
        
        _vertices[i] = {{verts[i].x*dx - _boundingBox.size.width*anchorPoint.x*dx,
            verts[i].y*dy - _boundingBox.size.height*anchorPoint.y*dy,
            Z_POS}, color};
        
        _screenVerts[i] = { verts[i].x, verts[i].y };
        Indices[i] = i;
    }
    
    _vertsN = vertsN;
    
//    setPosition({ _boundingBox.origin.x + _boundingBox.size.width/2, _boundingBox.origin.y + _boundingBox.size.height/2 });
    
    setupDraw();
}

void Stone::setupDraw()
{
    eval();
    
    setShaderProgram(kShaderColor);
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
}

int Stone::getHits()
{
    return _hits;
}

void Stone::callback()
{
    GameScene *parent = (GameScene *)getParent();
    parent->stoneCallback(this);
}

void Stone::render()
{
    if (!isVisible())
        return;
    
    setShaderProgram(kShaderColor);
    getShaderProgram()->use();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(0, 0, _winSize.width, _winSize.height);
    
    glUniformMatrix4fv(_mvLocation, 1, 0, _modelView.glMatrix());
    
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

    glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(AVertexColor), 0);
    glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(AVertexColor), (GLvoid*) (sizeof(float) * 3));
    
    glDrawElements(GL_TRIANGLE_FAN, _vertsN, GL_UNSIGNED_BYTE, 0);
}

//Using jarvis alg
void Stone::generateVerts()
{
    maxSize = STONE_MAX_SIZE;
    vector<int> H;
    vector<int> indexes;
    APoint *verts;
    
    do {
        _vertsN = MIN_VERTS + (rand() % (MAX_VERTS - MIN_VERTS));
        verts = new APoint[_vertsN];
        
        for (int i = 0; i < _vertsN; i++) {
            verts[i].x = fabs(rand() % (int)(maxSize));
            verts[i].y = fabs(rand() % (int)(maxSize));
            indexes.push_back(i);
        }
        
        for (int i = 1; i < _vertsN; i++) {
            if (verts[indexes[i]].x < verts[indexes[0]].x) {
                int tmp = indexes[0];
                indexes[0] = indexes[i];
                indexes[i] = tmp;
            }
        }
        
        H.push_back(indexes[0]);
        indexes.erase(indexes.begin());
        indexes.push_back(H[0]);
        
        while (true)
        {
            int right = 0;
            for (int i = 1; i < indexes.size(); i++) {
                if (direction(verts[H[H.size() - 1]], verts[indexes[right]], verts[indexes[i]]) < 0) {
                    right = i;
                }
            }
            
            if (indexes[right] == H[0]) {
                break;
            }
            else {
                H.push_back(indexes[right]);
                indexes.erase(indexes.begin() + right);
            }
        }
        
        if (H.size() < MIN_ANGLES) {
            indexes.erase(indexes.begin(), indexes.end());
            H.erase(H.begin(), H.end());
            delete [] verts;
        }
        
    } while (H.size() < MIN_ANGLES);
    
    float dx = 2.0f/_winSize.width;
    float dy = 2.0f/_winSize.height;
    
    _screenVerts = new APoint[H.size()];
    
    AColor color = {DEF_COLOR};
    float dcolor = (-DCOLOR/2 + (rand() % DCOLOR))/255.0f;
    color.r += dcolor;
    color.g += dcolor;
    color.b += dcolor;
    
    APoint left = {0, 0};
    APoint right = left;
    APoint up = left;
    APoint down = left;
    
    for (int i = 0; i < H.size(); i++) {
        APoint point = verts[H[i]];
        
        if (point.x < left.x) {
            left = point;
        }
        if (point.x > right.x) {
            right = point;
        }
        if (point.y < down.y) {
            down = point;
        }
        if (point.y > up.y) {
            up = point;
        }
    }
    
    float width = right.x - left.x;
    float height = up.y - down.y;
    
    ARect _boundingBox = { left.x, down.y, width - left.x, height - down.y };
    setBoundingBox(_boundingBox);
    
    APoint anchorPoint = getAnchorPoint();
    for (int i = 0; i < H.size(); i++) {
        
        _vertices[i] = {{verts[H[i]].x*dx - _boundingBox.size.width*anchorPoint.x*dx - left.x*dx,
                         verts[H[i]].y*dy - _boundingBox.size.height*anchorPoint.y*dy - down.y*dy,
                         Z_POS}, color};
        
        _screenVerts[i] = { verts[H[i]].x - left.x, verts[H[i]].y - down.y};
        Indices[i] = i;
    }
    
    _vertsN = H.size();
    
    delete [] verts;
}

int Stone::direction(APoint a, APoint b, APoint c)
{
    return (b.x - a.x)*(c.y - b.y)-(b.y - a.y)*(c.x - b.x);
}

const APoint *Stone::getScreenVerts()
{
    return _screenVerts;
}

int Stone::getVertsNumber()
{
    return _vertsN;
}

ARect Stone::getBoundingBox()
{
    ARect rect = Node::getBoundingBox();
    APoint position = getPosition();
    return { position.x - rect.size.width/2, position.y - rect.size.height/2, rect.size.width, rect.size.height };
}

void Stone::setPosition(const APoint &position)
{
    Node::setPosition(position);
    eval();
}

void Stone::setPosition(float x, float y)
{
    setPosition({x, y});
}

void Stone::setRotation(const float rotation)
{
    Node::setRotation(rotation);
    eval();
}

void Stone::eval()
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

Stone::~Stone()
{
    delete [] _screenVerts;
}