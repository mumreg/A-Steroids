//
//  Utils.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 27.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include <OpenGLES/ES2/gl.h>

#include "Utils.h"
#include "FileUtils.h"
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
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    float scale = [[UIScreen mainScreen] scale];
    
    CGRect myBounds = CGRectMake(screenBounds.origin.x, screenBounds.origin.y,
                                 screenBounds.size.height*scale, screenBounds.size.width*scale);
    
    return {myBounds.size.width, myBounds.size.height};
}

bool rectContainsPoint(ARect *rect, APoint *point)
{
    if ((point->x < rect->origin.x + rect->size.width && point->x > rect->origin.x) &&
        (point->y < rect->origin.y + rect->size.height && point->y > rect->origin.y)) {
        return true;
    }
    
    return false;
}