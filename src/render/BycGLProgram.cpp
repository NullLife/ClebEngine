//
//  BycGLProgram.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycGLProgram.h"

#include "BycGLShader.h"
#include "BycGLShaderParameters.h"

BycGLProgram::BycGLProgram() : _id(0), _linked(false) {

} 

BycGLProgram::~BycGLProgram() {
    _destroyShaders();
    _destroy();
}

void BycGLProgram::attach(BycGLShader *shader) {
    auto iter = std::find(_shaders.begin(), _shaders.end(), shader);
    if (iter == _shaders.end())
        _shaders.push_back(shader);
    else
        *iter = shader;
}

BycGLShader* BycGLProgram::createShader(GLenum shaderType) {
    BycGLShader* shader = new BycGLShader();
    shader->setType(shaderType);
    _shaders.push_back(shader);
    return shader;
}

BycGLShader* BycGLProgram::createShader(GLenum shaderType, String filePath) {
    BycGLShader* shader = new BycGLShader(shaderType, filePath);
    _shaders.push_back(shader);
    return shader;
}

void BycGLProgram::active() { 
    if (!_linked || _id == 0)
        _compileAndLink();
    
    CHECK_GL_ERROR(glUseProgram(_id));
}

const GLuint BycGLProgram::getId() {
    return _id;
}

void BycGLProgram::bindParam() {
    assert(_id > 0);
    
    for (BycGLShader* shader : _shaders) {
        shader->getParameters()->_bindParams(_id);
    }
}

void BycGLProgram::commitParamDataToGPU() {
    assert(_id > 0);
    
    for (BycGLShader* shader : _shaders) {
        shader->getParameters()->_updateParamsToGPU();
    }
}

void BycGLProgram::_compileAndLink() {
    // Create the program object.
    _id = glCreateProgram();
    assert(_id != 0);
        
    // Compile all the shaders and Attach to program.
    for (BycGLShader* shader : _shaders) {
        if (shader->_compile()) {
            glAttachShader(_id, shader->getId());
        }
    }

    // Link the shaders together.
    glLinkProgram(_id);

    // Detach all the shaders.
    for (BycGLShader* shader : _shaders) {
        glDetachShader(_id, shader->getId());
    }

    // Check.
    GLint status = -1;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        String msg;
        GLint infoLogLength;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(_id, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteProgram(_id);
        _id = 0;
        printf("Errors: link \n%s\n", msg.c_str());

        _linked = false;

        return;
    }

    _linked = true;
}

void BycGLProgram::_destroyShaders() {
    auto iter = _shaders.begin();
    for (; iter!=_shaders.end(); ++iter) {
        delete *iter;
        _shaders.erase(iter);
    }
    _shaders.shrink_to_fit();
}

void BycGLProgram::_destroy() {
    if (_id != 0) {
        glDeleteProgram(_id);
        _id = 0;
    }
    _linked = false;
}

