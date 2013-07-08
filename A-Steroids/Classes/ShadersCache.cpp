//
//  ShadersCache.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "ShadersCache.h"

const char *shaderNames[] = {kShaderTextureAndColor, kShaderColor};

ShadersCache *ShadersCache::sharedInstance()
{
    static ShadersCache *p_SC = NULL;
    if (p_SC == NULL) {
        p_SC = new ShadersCache();
    }
    
    return p_SC;
}

ShadersCache::ShadersCache()
{
    for (int i = 0; i < SHADERS_N; i++) {
        _shaderPrograms[i] = new ShaderProgram(shaderNames[i]);
    }
}

ShaderProgram *ShadersCache::getProgram(const char *key)
{
    for (int i = 0; i < SHADERS_N; i++) {
        if (std::string(shaderNames[i]) == std::string(key)) {
            return _shaderPrograms[i];
        }
    }
    
    return NULL;
}
