//
//  Utils.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 27.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Utils__
#define __A_Steroids__Utils__

#include <iostream>
#include "datatypes.h"

extern unsigned char * readFileToBuffer(const char *fileName);
extern void setMatrixIdentity(float *mat, int n);
extern void glCheckError();
extern ASize getWinSize();
extern bool rectContainsPoint(ARect *rect, APoint *point);
extern float scalarMult(APoint vec1, APoint vec2);
extern float vecLength(APoint vec);
extern APoint vectorMult(APoint vec1, APoint vec2);

#endif /* defined(__A_Steroids__Utils__) */
