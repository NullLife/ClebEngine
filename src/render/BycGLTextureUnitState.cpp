//
//  BycGLTextureUnitState.cpp
//  BycRun
//
//  Created by FengMap on 2018/2/18.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycGLTextureUnitState.h"

#include "BycSceneManager.h"
#include "BycImage.h"

#include "BycMaterial.h"
#include "BycPass.h"
#include "BycGLTextureCache.h"
#include "BycGLTexture.h"

BycGLTextureUnitState::BycGLTextureUnitState() :
_tex(nullptr),
_isLoaded(false),
_parent(nullptr),
_name(""),
_alias(""),
_unit(0),
_type(GL_TEXTURE_2D),
_attachment(GL_COLOR_ATTACHMENT0) {
    _uvw.u = WrapOption::CLAMP;
    _uvw.v = WrapOption::CLAMP;
    _uvw.w = WrapOption::WO_NONE;
    
    _minFilter = FilterOption::LINEAR;
    _magFilter = FilterOption::LINEAR;
    _mipFilter = FilterOption::FO_NONE;

} 

BycGLTextureUnitState::~BycGLTextureUnitState() {
}

void BycGLTextureUnitState::setName(const String& name) {
    _name = name;
}

const String& BycGLTextureUnitState::getName() const {
    return _name;
}

void BycGLTextureUnitState::setParent(BycPass* parent) {
    _parent = parent;
}

BycPass* BycGLTextureUnitState::getParent() {
    return _parent;
}


void BycGLTextureUnitState::setAlias(const String& alias) {
    _alias = alias;
}
const String& BycGLTextureUnitState::getAlias() const {
    return _alias;
}

void BycGLTextureUnitState::setTextureType(GLenum type) {
    _type = type;
}

const GLenum BycGLTextureUnitState::getTextureType() const {
    return _type;
}

void BycGLTextureUnitState::setAttachment(GLenum attachment) {
    _attachment = attachment;
}

const GLenum BycGLTextureUnitState::getAttachment() const {
    return _attachment;
}

void BycGLTextureUnitState::setFiltering(FilterType type, FilterOption opt) {
    switch (type) {
        case MIN:
            _minFilter = opt;
            return;
        case MAG:
            _magFilter = opt;
            return;
        case MIP:
            _mipFilter = opt;
            return;
            
        default:
            _minFilter = opt;
            return;
    }
}

void BycGLTextureUnitState::setFiltering(FilterOption minFilter, FilterOption magFilter, FilterOption mipFilter) {
    _minFilter = minFilter;
    _magFilter = magFilter;
    _mipFilter = mipFilter;
}

const BycGLTextureUnitState::FilterOption& BycGLTextureUnitState::getFiltering(FilterType type) {
    switch (type) {
        case MIN:
            return _minFilter;
        case MAG:
            return _magFilter;
        case MIP:
            return _mipFilter;
        default:
            return _minFilter;
    }
}

void BycGLTextureUnitState::setWrap(WrapOption wrap) {
    _uvw.u = wrap;
    _uvw.v = wrap;
    _uvw.w = wrap;
}

void BycGLTextureUnitState::setWrap(WrapOption u, WrapOption v, WrapOption w) {
    _uvw.u = u;
    _uvw.v = v;
    _uvw.w = w;
}

void BycGLTextureUnitState::setWrap(const UVWWrap& uvw) {
    _uvw = uvw;
}

const BycGLTextureUnitState::UVWWrap& BycGLTextureUnitState::getUVWWrap() {
    return _uvw;
}

void BycGLTextureUnitState::setImages(const Vector<int>& indices) {
    _imageIndices.clear();
    _imageIndices.insert(_imageIndices.begin(), indices.begin(), indices.end());
}

void BycGLTextureUnitState::setUnit(int unit) {
    _unit = unit;
}

int BycGLTextureUnitState::getUnit() {
    return _unit;
}

BycGLTexture* BycGLTextureUnitState::getTexture() {
    return _tex;
}

bool BycGLTextureUnitState::load(BycSceneManager* manager) {
    if (_isLoaded)
        return true;
    
    switch (_type) {
        case GL_TEXTURE_2D:
            _isLoaded = load2DTexture(manager);
            break;
            
        case GL_TEXTURE_CUBE_MAP:
            break;
            
        default:
            break;
    }
    
    return _isLoaded;
}

bool BycGLTextureUnitState::load2DTexture(BycSceneManager* manager) {
    const String& file = _parent->getParent()->getImage(_imageIndices[0]);
    
    BycGLTextureCache* texCache = manager->getGLTextureCache();
    _tex = texCache->get(file);
    if (_tex == nullptr) {
        _tex = new BycGLTexture(file, _type);
        texCache->add(_tex);

        // Read image data.
        BycImage* image = new BycImage();
        bool ret = image->loadImage(file);
        if (!ret) {
            printf("BycGLTextureUnitState: \n%s \n path: %s\n", "Fail to load texture", file.c_str());
            return false;
        }

        const unsigned char* buffer = image->getBuffer();
        if (!buffer)
            return false;

        // Set texture content.
        _tex->texImage(0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        // Free image.
        delete image;
    }

    return true;
}


