//
//  matrx4.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 29.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__matrx4__
#define __A_Steroids__matrx4__

#include <iostream>

#define MAT_SIZE    4

class matrix4 {
public:
    matrix4();
    matrix4(float fillNumber);
    
    void setIdentity();
    float *glMatrix();
    
    matrix4 operator*(matrix4 &inMat);
private:
    void initMatrix(float fillNumber);
    float _matrix[MAT_SIZE*MAT_SIZE];
};

#endif /* defined(__A_Steroids__matrx4__) */
