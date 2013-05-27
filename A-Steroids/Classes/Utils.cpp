//
//  Utils.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 27.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Utils.h"

void readFileToBuffer(const char *fileName, unsigned char *buffer)
{
    unsigned long size = 0;
    FILE *fd = fopen(fileName, "r");
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    buffer = new unsigned char[size];
    fread(buffer, sizeof(unsigned char), size, fd);
    fclose(fd);
}