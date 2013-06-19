//
//  datatypes.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef A_Steroids_datatypes_h
#define A_Steroids_datatypes_h

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

typedef struct _ImageInfo {
    ASize size;
    const char *data;
} ImageInfo;

#endif
