//
//  BycGLRenderSystem.h
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLRenderSystem_h
#define BycGLRenderSystem_h

#include "BycDefinitions.h"

#include "BycGLTextureUnitState.h"

class BycSceneManager;
class BycPass;
class BycGLProgram;
class BycRenderOpt;

class BycGLRenderSystem {
public:
    typedef HashMap<std::uint64_t, BycGLProgram*> ProgramKV;
    
    BycGLRenderSystem(BycSceneManager* sceneManager);
    ~BycGLRenderSystem();
    
    void _usePass(BycPass* pass);
    
    void draw(BycRenderOpt& opt, BycPass* pass);
      
private:
    BycGLProgram* getProgram(std::uint64_t key);
    void setTextureState(BycGLTextureUnitState* texState);
    void setTextureUnitFiltering(GLenum texType, BycGLTextureUnitState::FilterType filterType, BycGLTextureUnitState::FilterOption opt);
    void setTextureWrap(GLenum texType, BycGLTextureUnitState::UVWWrap uvw);
    
    BycSceneManager* _sceneManager;
    ProgramKV _programs;
    
    mutable BycGLProgram* _currProgram;
};

#endif /* BycGLRenderSystem_h */
