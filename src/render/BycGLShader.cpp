//
//  BycGLShader.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycGLShader.h"
#include "BycGLShaderParameters.h"

#include "BycIOUtils.h"

BycGLShader::BycGLShader() :
        _name(""), _filePath(""), _language("glsl"), _version("410"), _type(GL_VERTEX_SHADER), _id(0),
        _params(new BycGLShaderParameters()),
        _compiled(false) {

}

BycGLShader::BycGLShader(const GLenum shaderType, const String &filePath) :
        _name(filePath), _filePath(filePath), _language("glsl"), _version("410"), _type(shaderType), _id(0),
        _params(new BycGLShaderParameters()),
        _compiled(false) {

}

BycGLShader::~BycGLShader() {
    delete _params;
    _params = nullptr;
}

void BycGLShader::setUniqueName(const String &name) {
    _name = name;
}

const String &BycGLShader::getUniqueName() const {
    return _name;
}


void BycGLShader::setType(const GLenum type) {
    _type = type;
}


const GLenum BycGLShader::getType() const {
    return _type;
}


void BycGLShader::setLanguage(const std::string &language) {
    _language = language;
}


const String &BycGLShader::getLanguage() const {
    return _language;
}


void BycGLShader::setLanguageVersion(const String &version) {
    _version = version;
}

const String &BycGLShader::getLanguageVersion() const {
    return _version;
}

const GLuint BycGLShader::getId() const {
    return _id;
}

const bool BycGLShader::_compile(bool force) {
    if (_compiled && !force)
        return true;

    std::string source = BycIOUtils::readFile(_filePath);
    if (source.empty())
        assert(false);

    String desc = "";
    switch (_type) {
        case GL_VERTEX_SHADER:
            desc = "VERTEX_SHADER";
            break;

        case GL_FRAGMENT_SHADER:
            desc = "FRAGMENT_SHADER";
            break;

        default:
            break;
    }

    printf("\n=============== %s ===============\n", "Compile shader");
    printf("shader type: [%s]\n", desc.c_str());
    printf("shader file: [%s]\n", _filePath.c_str());

    // Create the shader object
    _id = glCreateShader(_type);
    assert(_id != 0);

    const char *code = source.c_str();
    glShaderSource(_id, 1, &code, nullptr);

    // Compile.
    glCompileShader(_id);

    // Check.
    GLint status;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg;
        GLint       infoLogLength;
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(_id, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(_id);
        _id = 0;

        printf("Errors: [%s]\n", msg.c_str());

        return false;
    }

    printf("compiling result: [%s]\n", "Success.");

    printf("\n%s\n", "=======================================");

    return _compiled = true;
}

BycGLShaderParameters *BycGLShader::getParameters() {
    return _params;
}

void BycGLShader::addUniformParameter(BycGLShaderParamField::FieldContent content,
                                      BycGLShaderParamField::FieldDataType dataType,
                                      int index) {
    _params->addUniformParameter(content, dataType, index);
}