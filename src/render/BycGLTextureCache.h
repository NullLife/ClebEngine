//
//  BycGLTextureCache.h
//  BycRun
//
//  Created by FengMap on 2018/2/12.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLTextureCache_h
#define BycGLTextureCache_h

#include "BycDefinitions.h"

class BycSceneManager;
class BycGLTexture;

class BycGLTextureCache {
    friend class BycSceneManager;
public:
    typedef HashMap<String, BycGLTexture*> TexCache;
    
    void add(BycGLTexture* tex);
    BycGLTexture* get(const String& name);
    void release(const String& name);
    
private:
    BycGLTextureCache();
    ~BycGLTextureCache();
    
    TexCache _cache;
};

#endif /* BycGLTextureCache_h */
