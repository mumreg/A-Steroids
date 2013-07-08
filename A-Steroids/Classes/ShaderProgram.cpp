//
//  ShaderProgram.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "ShaderProgram.h"
#include "Utils.h"

using namespace std;

ShaderProgram::ShaderProgram(const char *shaderName)
{
    string vertexName = string(shaderName) + string(".vsh");
    _vertexBuffer = readFileToBuffer(vertexName.c_str());
    
    string fragmentName = string(shaderName) + string(".fsh");
    _fragmentBuffer = readFileToBuffer(fragmentName.c_str());
    
    if (_fragmentBuffer != NULL && _vertexBuffer != NULL) {
        
        _vertexShader = compileShader(GL_VERTEX_SHADER, (GLchar *)_vertexBuffer);
        _fragmentShader = compileShader(GL_FRAGMENT_SHADER, (GLchar *)_fragmentBuffer);
        
        _program = glCreateProgram();
        
        if (_vertexShader != -1 && _fragmentShader != -1) {
            glAttachShader(_program, _vertexShader);
            glAttachShader(_program, _fragmentShader);
            linkShader();
        }
        else {
            printf("Error! While compiling shaders\n");
        }
    }
    else {
        printf("Error! Couldn't read shader files!\n");
    }
}

void ShaderProgram::use()
{
    glUseProgram(_program);
}

GLuint ShaderProgram::compileShader(GLenum type, const GLchar *source)
{
    string tmpStr = string((const char *)source);
    const GLint len = tmpStr.length();
    GLint status = -1;
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, &len);
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLchar messages[256];
        glGetShaderInfoLog(shader, sizeof(messages), 0, &messages[0]);
        printf("Shader compiling %s", messages);
        exit(1);
    }
    else
        return shader;
}

GLuint ShaderProgram::getProgram()
{
    return _program;
}

void ShaderProgram::linkShader()
{
    glLinkProgram(_program);
    
    GLint linkSuccess;
    glGetProgramiv(_program, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(_program, sizeof(messages), 0, &messages[0]);
        printf("Link shader %s", messages);
        exit(1);
    }
}

