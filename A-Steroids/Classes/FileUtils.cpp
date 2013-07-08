//
//  FileUtils.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "FileUtils.h"
#import "FileUtils_objc.h"

const char * FileUtils::getFullPath(const char *fileName)
{
    return [FileUtils_objc getFullPathFor:[NSString stringWithCString:fileName encoding:NSUTF8StringEncoding]];
}