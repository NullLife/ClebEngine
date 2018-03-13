//
//  BycGLRenderSystem.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycGLRenderSystem.h"

#include "BycSceneManager.h"

#include "BycDrawable.h"
#include "BycMaterial.h"
#include "BycPass.h"
#include "BycGLProgram.h"
#include "BycGLShader.h"
#include "BycGLShaderParameters.h"
#include "BycGLTextureCache.h"
#include "BycGLTexture.h"

#include "BycEntity.h"


BycGLRenderSystem::BycGLRenderSystem(BycSceneManager* sceneManager) :
_sceneManager(sceneManager),
_currProgram(nullptr) {
} 

BycGLRenderSystem::~BycGLRenderSystem() {
}

void BycGLRenderSystem::_usePass(BycPass* pass) {
    // Get or create program.
    std::uint64_t key = 0;
    const BycPass::GLShaderArr& shaders = pass->getShaders();
    for (BycGLShader* shader : shaders) {
        assert(shader->_compile());
        GLuint shaderId = shader->getId();
        switch (shader->getType()) {
            case GL_VERTEX_SHADER:
                key += static_cast<std::uint64_t>(shaderId) << 16;
                break;
            case GL_FRAGMENT_SHADER:
                key += static_cast<std::uint64_t>(shaderId) << 63;
                break;
        }
    }
    
    _currProgram = getProgram(key);
    if (_currProgram == nullptr) {
        BycGLProgram* program = new BycGLProgram();
        for (BycGLShader* shader : shaders) {
            program->attach(shader);
        }
        _programs.insert(ProgramKV::value_type(key, program));
        _currProgram = program;
    }
}

void BycGLRenderSystem::draw(BycRenderOpt& opt, BycPass* pass) {
    _currProgram->active();
    // Bind parameters.
    for (BycGLShader* shader : pass->getShaders()) {
        BycGLShaderParameters* params = shader->getParameters();
        params->_bindParams(_currProgram->getId());
    }
    _currProgram->commitParamDataToGPU();

    // set textures.
    for (BycGLTextureUnitState* state : pass->getGLTextureUnitStates()) {
        setTextureState(state);
    }

    glDrawElements(GL_TRIANGLES, (GLsizei) opt._count, GL_UNSIGNED_INT, 0);
}

void BycGLRenderSystem::setTextureState(BycGLTextureUnitState* texState) {
    // Make sure the texture is be ready.
    bool ret = texState->load(_sceneManager);
    if (!ret) {
        // Load texture failure, then return it.
        // FixMe: Considering using a default texture here...?
        return;
    }

    BycGLTexture* tex = texState->getTexture();
    const GLenum texType = texState->getTextureType();

    tex->bind();
    
    // Filtering.
    bool isMipmap = (texState->getFiltering(BycGLTextureUnitState::FilterType::MIP) != BycGLTextureUnitState::FilterOption::FO_NONE);
    if (isMipmap) {
        /// Mipmap...
    } else {
        CHECK_GL_ERROR(glTexParameteri(texType, GL_TEXTURE_BASE_LEVEL, 0));
        CHECK_GL_ERROR(glTexParameteri(texType, GL_TEXTURE_MAX_LEVEL, 0));

        setTextureUnitFiltering(texType, BycGLTextureUnitState::FilterType::MIN, texState->getFiltering(BycGLTextureUnitState::FilterType::MIN));
        setTextureUnitFiltering(texType, BycGLTextureUnitState::FilterType::MAG, texState->getFiltering(BycGLTextureUnitState::FilterType::MAG));
    }

    // Wrapping.
    const BycGLTextureUnitState::UVWWrap& uvw = texState->getUVWWrap();
    setTextureWrap(texType, uvw);

//    // Bind texture.
//    glActiveTexture((GLenum) (GL_TEXTURE0 + texState->getUnit()));
//    glBindTexture(texType, texState->getTexture()->getId());
}

void BycGLRenderSystem::setTextureUnitFiltering(GLenum texType, BycGLTextureUnitState::FilterType filterType, BycGLTextureUnitState::FilterOption opt) {
    switch (filterType) {
        case BycGLTextureUnitState::FilterType::MIN: {
            if (opt == BycGLTextureUnitState::FilterOption::NEAR)
                glTexParameterf(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            else
                glTexParameterf(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
            break;
            
        case BycGLTextureUnitState::FilterType::MAG: {
            if (opt == BycGLTextureUnitState::FilterOption::NEAR)
                glTexParameterf(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            else
                glTexParameterf(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
            break;
            
        case BycGLTextureUnitState::FilterType::MIP: {
            if (opt == BycGLTextureUnitState::FilterOption::NEAR) {
                glTexParameterf(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                glTexParameterf(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            } else if (opt == BycGLTextureUnitState::FilterOption::LINEAR) {
                glTexParameterf(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameterf(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
            
        }
            break;
    }
}

void BycGLRenderSystem::setTextureWrap(GLenum texType, BycGLTextureUnitState::UVWWrap uvw) {
    glTexParameterf(texType, GL_TEXTURE_WRAP_S, uvw.u);
    glTexParameterf(texType, GL_TEXTURE_WRAP_T, uvw.v);
    if (uvw.w != BycGLTextureUnitState::WrapOption::WO_NONE)
        glTexParameterf(texType, GL_TEXTURE_WRAP_R, uvw.w);
}

BycGLProgram* BycGLRenderSystem::getProgram(std::uint64_t key) {
    auto iter = _programs.find(key);
    if (iter == _programs.end())
        return nullptr;
    
    return iter->second;
}
