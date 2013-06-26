//
//  Image.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Image.h"
#include "Image_objc.h"

Image::Image(const char *fileName)
{
    _imageInfo = [Image_objc getImageData:fileName];
}

ASize Image::getImageSize()
{
    ASize size = {0, 0};
    
    if (_imageInfo != NULL) {
       size = _imageInfo->size;
    }
    
    return size;
}

const GLubyte *Image::getImageData()
{
    if (_imageInfo != NULL) {
        return _imageInfo->data;
    }
    
    return NULL;
}

Image::~Image()
{
    if (_imageInfo != NULL) {
        delete _imageInfo;
    }
}