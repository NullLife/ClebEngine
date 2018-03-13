//
//  BycGLTexture.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycGLTexture.h"

BycGLTexture::BycGLTexture(const String &name, GLenum type) :
        _name(name),
        _type(type) {

    CHECK_GL_ERROR(glGenTextures(1, &_id));

    printf("New texture: id(%d) name(%s)\n", _id, _name.c_str());
}

BycGLTexture::~BycGLTexture() {
    if (_id > 0) {
        printf("Delete texture: %s\n", _name.c_str());

        CHECK_GL_ERROR(glDeleteTextures(1, &_id));
    }
}

const String &BycGLTexture::getName() const {
    return _name;
}

const GLenum BycGLTexture::getType() const {
    return _type;
}

const GLuint BycGLTexture::getId() const {
    return _id;
}


void BycGLTexture::bind() {
    if (_id == 0)
        assert(false);

    CHECK_GL_ERROR(glBindTexture(_type, _id));
}

void BycGLTexture::texImage(GLint level, GLint internalFormat,
                            GLsizei width, GLsizei height,
                            GLint border, GLenum format,
                            GLenum dataType, const GLvoid *data) {
    bind();

    CHECK_GL_ERROR(glTexImage2D(_type, level, internalFormat, width, height, border, format, dataType, data));
}
