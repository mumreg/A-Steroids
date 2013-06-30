//
//  datatypes.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef A_Steroids_datatypes_h
#define A_Steroids_datatypes_h

#include <OpenGLES/ES2/gl.h>

#define DegreesToRadiansFactor  0.017453292519943f			// PI / 180
#define MAX_TOUCHES             10

typedef struct _Point {
    float x;
    float y;
} APoint;

typedef struct _Size {
    float width;
    float height;
} ASize;

typedef struct _Rect {
    APoint origin;
    ASize size;
} ARect;

typedef struct _Color {
    float r;
    float g;
    float b;
    float a;
} AColor;

typedef struct _TexCoords {
    float x;
    float y;
} ATexCoords;

typedef struct _ImageInfo {
    ASize size;
    GLubyte *data;
} ImageInfo;

typedef struct _Vertex {
    float position[3];
    AColor color;
    ATexCoords TexCoord; // New
} AVertex;

#endif
