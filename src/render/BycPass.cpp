//
//  BycPass.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycPass.h"

#include "BycGLShader.h"
#include "BycGLShaderParameters.h"
#include "BycGLTextureUnitState.h"

BycPass::BycPass() : _name(""), _parent(nullptr) {

} 

BycPass::~BycPass() {
    destroyedShaders();
}

void BycPass::setName(const String& name) {
    _name = name;
}

const String& BycPass::getName() const {
    return _name;
}

void BycPass::setParent(BycMaterial* mtl) {
    _parent = mtl;
}

BycMaterial* BycPass::getParent() {
    return _parent;
}

BycGLShader* BycPass::createShader(GLenum shaderType, const String& path) {
    BycGLShader* shader = new BycGLShader(shaderType, path);
    
    _shaders.push_back(shader);
    
    return shader;
}

void BycPass::addShader(BycGLShader* shader) {
    _shaders.push_back(shader);
}

void BycPass::updateGLShaderParameters(BycParamsDataSource* dataSource) {
    for (BycGLShader* shader : _shaders) {
        shader->getParameters()->updateLocalParams(dataSource);
    }
}

const BycPass::GLShaderArr& BycPass::getShaders() {
    return _shaders;
}

BycGLTextureUnitState* BycPass::createGLTextureUnitState(const String& name) {
    for (BycGLTextureUnitState* tex : _texUnitStates) {
        if (tex->getName() == name)
            assert(false);
    }
    
    BycGLTextureUnitState* tex = new BycGLTextureUnitState();
    tex->setName(name);
    tex->setParent(this);
    
    _texUnitStates.push_back(tex);
    
    return tex;
}

const BycPass::GLTexUnitStateArr& BycPass::getGLTextureUnitStates() {
    return _texUnitStates;
}

void BycPass::destroyedShaders() {
    auto iter = _shaders.begin();
    for (; iter != _shaders.end(); ++iter) {
        delete *iter;
        _shaders.erase(iter);
    }
    _shaders.shrink_to_fit();
}
