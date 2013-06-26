//
//  ShaderProgram.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 27.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__ShaderProgram__
#define __A_Steroids__ShaderProgram__

#include <iostream>
#include "GameConfig.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define kShaderTextureAndColor "Texture_and_color"

#define kShaderMVUniform        "modelView"
#define kShaderProjectUniform   "projection"
#define kShaderTextureUniform   "texture"

#define kShaderPositionAttr     "position"
#define kShaderTextureAttr      "texCoordIn"
#define kShaderColorAttr        "colorIn"

class ShaderProgram {
public:
    ShaderProgram(const char *shaderName);
    void linkShader();
    void updateUniforms();
    void use();
    void setBuiltinUniforms();
    GLuint getProgram();
    
private:
    GLuint compileShader(GLenum type, const GLchar *source);
    
    unsigned char *_vertexBuffer;
    unsigned char *_fragmentBuffer;
    
    GLuint _vertexShader;
    GLuint _fragmentShader;
    GLuint _program;
};

#endif /* defined(__A_Steroids__ShaderProgram__) */
