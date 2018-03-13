//
// Created by yangbin on 2018/3/11.
//

#include "BycMultiRenderTarget.h"

#include "BycStringUtils.h"

#include "BycFBO.h"
#include "BycGLTexture.h"

BycMultiRenderTarget::BycMultiRenderTarget(const String &name, int width, int height) {
    _fbo        = new BycFBO(name, width, height);
    _depthTex   = nullptr;
    _isPrepared = false;

    _buffers = nullptr;
}

BycMultiRenderTarget::~BycMultiRenderTarget() {
    delete _fbo;
    if (_depthTex)
        delete _depthTex;
}


BycMultiRenderTarget *BycMultiRenderTarget::addRenderTarget(const MRTContent content) {
    BycGLTexture *tex = new BycGLTexture("", GL_TEXTURE_2D);
    if (content == DEPTH) {
        if (_depthTex != nullptr)
            delete _depthTex;

        _depthTex = tex;
    } else {
        // Can't add the content twice.
        auto iter = _textures.find(content);
        if (iter != _textures.end()) {
            printf("BycMultiRenderTarget::addRenderTarget errors \n[%s]", "Can't add the content twice.");
            return this;
        }

        _textures.insert(BycMultiRenderTarget::RTTextureKV::value_type(content, tex));
    }

    return this;
}

BycGLTexture *BycMultiRenderTarget::getTexture(const MRTContent content) {
    auto iter = _textures.find(content);
    if (iter == _textures.end())
        return nullptr;

    return iter->second;
}

void BycMultiRenderTarget::prepare() {
    if (_isPrepared)
        return;

    _fbo->bind();

    int width  = _fbo->getWidth();
    int height = _fbo->getHeight();

    int i      = 0;
    int bufLen = (int) _textures.size();
    // Depth
    if (_depthTex) {
        _buffers = new GLenum[bufLen + 1];

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        CHECK_GL_ERROR(
                glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTex->getId(), 0));

        const GLenum type = _depthTex->getType();
        glTexParameterf(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        _buffers[i] = GL_NONE;

        ++i;

    } else {
        _buffers = new GLenum[bufLen];
    }

    // Others
    for (RTTextureKV::value_type vt : _textures) {
        vt.second->texImage(0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
        const GLenum type = vt.second->getType();
        glTexParameterf(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        CHECK_GL_ERROR(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, vt.second->getType(),
                                              vt.second->getId(), 0));

        _buffers[i] = (GLenum) (GL_COLOR_ATTACHMENT0 + i);

        ++i;
    }

    CHECK_GL_ERROR(glDrawBuffers(bufLen, _buffers));

    GLenum status = _fbo->check();
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        _fbo->unbind();
        printf("FrameBuffer error: %s \n [%s]", _fbo->getName().c_str(), BycStringUtils::toString((int)status).c_str());
        _isPrepared = false;
        return;
    }

    _isPrepared = true;
}

void BycMultiRenderTarget::bind() {
}

void BycMultiRenderTarget::unbind() {
}
