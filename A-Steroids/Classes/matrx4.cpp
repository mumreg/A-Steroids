//
//  matrx4.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 29.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "matrx4.h"

matrix4::matrix4()
{
    initMatrix(0.0f);
}

matrix4::matrix4(float fillNumber)
{
    initMatrix(fillNumber);
}

void matrix4::initMatrix(float fillNumber)
{
    for (int i = 0; i < MAT_SIZE*MAT_SIZE; i++) {
        _matrix[i] = fillNumber;
    }
}

void matrix4::setIdentity()
{
    initMatrix(0.0f);
    _matrix[0] = 1.0f;
    _matrix[5] = 1.0f;
    _matrix[10] = 1.0f;
    _matrix[15] = 1.0f;
}

float * matrix4::glMatrix()
{
    return _matrix;
}

matrix4 matrix4::operator*(matrix4 &inMat)
{
    matrix4 resultMatrix;
    float *result = resultMatrix.glMatrix();
    float *in = inMat.glMatrix();
    
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < MAT_SIZE; j++) {
            result[i + j*MAT_SIZE] = 0;
            for (int k = 0; k < MAT_SIZE; k++) {
                result[i + j*MAT_SIZE] = result[i + j*MAT_SIZE] + (_matrix[i + k*MAT_SIZE] * in[k + j*MAT_SIZE]);
            }
        }
    }
    
    for (int i = 0; i < MAT_SIZE*MAT_SIZE; i++) {
        _matrix[i] = result[i];
    }
    
    return *this;
}