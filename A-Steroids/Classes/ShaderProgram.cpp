//
//  ShaderProgram.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 27.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "ShaderProgram.h"
#include "Utils.h"

using namespace std;

ShaderProgram::ShaderProgram(const char *shaderName)
{
    string vertexName = string(shaderName) + string(".vsh");
    int vertexStatus = readFileToBuffer(vertexName.c_str(), _vertexBuffer);
    
    string fragmentName = string(shaderName) + string(".fsh");
    int fragmentStatus = readFileToBuffer(fragmentName.c_str(), _fragmentBuffer);
    
    if (fragmentStatus == 0 && vertexStatus == 0) {
        _program = glCreateProgram();
        
        _vertexShader = compileShader(GL_VERTEX_SHADER, (GLchar *)_vertexBuffer);
        _fragmentShader = compileShader(GL_FRAGMENT_SHADER, (GLchar *)_fragmentBuffer);
        
        if (_vertexShader != -1 && _fragmentShader != -1) {
            glAttachShader(_program, _vertexShader);
            glAttachShader(_program, _fragmentShader);
        }
    }
    else {
        printf("Error! Couldn't read shader files!");
    }
}

GLuint ShaderProgram::compileShader(GLenum type, const GLchar *source)
{
    GLint status;
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (!status)
        return -1;
    else
        return shader;
}

void ShaderProgram::linkShader()
{
    glLinkProgram(_program);
}

void ShaderProgram::addAttribute(const char *name, GLuint index)
{
    glBindAttribLocation(_program, index, (const GLchar *) name);
}

