//
//  ShadersCache.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 20.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__ShadersCache__
#define __A_Steroids__ShadersCache__

#include <iostream>
#include "ShaderProgram.h"

#define SHADERS_N   1

class ShadersCache {
public:
    static ShadersCache *sharedInstance();
    ShaderProgram *getProgram(const char *key);
    
private:
    ShadersCache();
    ShadersCache(ShadersCache &) {}
    ShadersCache& operator=(ShadersCache &);
    
    void addAttributes(ShaderProgram *program, int index);
    
    ShaderProgram *_shaderPrograms[SHADERS_N];
};

#endif /* defined(__A_Steroids__ShadersCache__) */
