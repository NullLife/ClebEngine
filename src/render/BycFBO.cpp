//
// Created by yangbin on 2018/3/11.
//

#include "BycFBO.h"

BycFBO::BycFBO(const String &name, int width, int height) :
        _name(name),
        _width(width),
        _height(height) {
    CHECK_GL_ERROR(glGenFramebuffers(1, &_id));
}

BycFBO::~BycFBO() {
    CHECK_GL_ERROR(glDeleteFramebuffers(1, &_id));
    _id = 0;
}

const String& BycFBO::getName() const {
    return _name;
}

int BycFBO::getWidth() const {
    return _width;
}

int BycFBO::getHeight() const {
    return _height;
}

void BycFBO::bind() {
    CHECK_GL_ERROR(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _id));
}

void BycFBO::unbind() {
    CHECK_GL_ERROR(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}

GLenum BycFBO::check() {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}