//
//  Image.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Image__
#define __A_Steroids__Image__

#include <iostream>
#include "datatypes.h"

class Image {
public:
    Image(const char *fileName);
    ~Image();
    
    ASize getImageSize();
    const GLubyte *getImageData();
private:
    ImageInfo *_imageInfo;
};

#endif /* defined(__A_Steroids__Image__) */
