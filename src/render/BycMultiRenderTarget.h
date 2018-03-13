//
// Created by yangbin on 2018/3/11.
//

#ifndef CLEBENGINE_BYCMULTIRENDERTARGET_H
#define CLEBENGINE_BYCMULTIRENDERTARGET_H

#include "BycDefinitions.h"

class BycFBO;
class BycGLTexture;

class BycMultiRenderTarget {
public:
    /// Render target contents.
    enum MRTContent {
        POSITION = 0,
        NORMAL,
        COLOR,
        DEPTH
    };

    /// Construct.
    BycMultiRenderTarget(const String& name, int width, int height);
    ~BycMultiRenderTarget();

    /// Add render target according to the content.
    BycMultiRenderTarget* addRenderTarget(const MRTContent content);

    /// Get the texture according to the content.
    BycGLTexture* getTexture(const MRTContent content);

    void prepare();

    void bind();

    void unbind();

private:
    typedef HashMap<int, BycGLTexture*> RTTextureKV;

    bool _isPrepared;

    BycFBO* _fbo;

    RTTextureKV _textures;

    BycGLTexture* _depthTex;

    GLenum* _buffers;
};


#endif //CLEBENGINE_BYCMULTIRENDERTARGET_H
