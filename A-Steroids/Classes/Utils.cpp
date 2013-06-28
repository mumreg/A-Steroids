//
//  Utils.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 27.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Utils.h"
#include "FileUtils.h"
#include <OpenGLES/ES2/gl.h>
#import "AppDelegate.h"

unsigned char * readFileToBuffer(const char *fileName)
{
    unsigned long size = 0;
    unsigned char *buffer;
    
    fileName = FileUtils::getFullPath(fileName);
    
    FILE *fd = fopen(fileName, "rb");
    if (fd != NULL) {
        fseek(fd, 0, SEEK_END);
        size = ftell(fd);
        fseek(fd, 0, SEEK_SET);

        buffer = new unsigned char[size + 1];
        fread(buffer, sizeof(unsigned char), size, fd);
        fclose(fd);
        
        buffer[size] = '\0';
        
        return buffer;
    }
    else {
        printf("Error opening file: %s\n", fileName);
        return NULL;
    }
}

void setMatrixIdentity(float *mat, int n)
{
    for (int i = 0; i < n; i++) {
        mat[i] = 1.0f;
    }
}

void glCheckError()
{
    int error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL error: 0x%X\n", error);
    }
}

ASize getWinSize()
{
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    
    float scale = [[UIScreen mainScreen] scale];
    
    return {screenWidth*scale, screenHeight*scale};
}
