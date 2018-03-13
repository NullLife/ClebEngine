//
//  BycGLTextureCache.cpp
//  BycRun
//
//  Created by FengMap on 2018/2/12.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "./BycGLTextureCache.h"

#include "./BycGLTexture.h"

BycGLTextureCache::BycGLTextureCache() {
} 

BycGLTextureCache::~BycGLTextureCache() {
    for (TexCache::value_type& val : _cache) {
        delete val.second;
    }
    _cache.clear();
}

void BycGLTextureCache::add(BycGLTexture* tex) {
    auto iter = _cache.find(tex->getName());
    if (iter == _cache.end())
        _cache.insert(TexCache::value_type(tex->getName(), tex));
}

BycGLTexture* BycGLTextureCache::get(const String& name) {
    auto iter = _cache.find(name);
    if (iter != _cache.end())
        return iter->second;
    return nullptr;
}

void BycGLTextureCache::release(const String& name) {
    auto iter = _cache.find(name);
    if (iter == _cache.end())
        return;
    
    delete iter->second;
    _cache.erase(iter);
}

