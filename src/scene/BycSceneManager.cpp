//
//  BycSceneManager.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycSceneManager.h"

#include "BycCamera.h"
#include "BycParamsDataSource.h"

#include "BycComponent.h"
#include "BycEntity.h"

#include "BycPointLight.h"
#include "BycDirectionalLight.h"
#include "BycSpotLight.h"

#include "BycGLRenderSystem.h"
#include "BycMaterial.h"
#include "BycPass.h"
#include "BycGLTextureCache.h"

BycSceneManager::BycSceneManager() : _currCamera(nullptr), _ambientColor(Vec4(1.0f)) {
    _renderSystem = new BycGLRenderSystem(this);

    _paramsDS = new BycParamsDataSource();
    _texCache = new BycGLTextureCache();
}

BycSceneManager::~BycSceneManager() {
    destroyComponentKV();
    destroyCameraKV();

    _currCamera = nullptr;

    delete _renderSystem;
    _renderSystem = nullptr;

    delete _paramsDS;
    _paramsDS = nullptr;

    delete _texCache;
    _texCache = nullptr;
}

BycParamsDataSource *BycSceneManager::getParamsDataSource() {
    return _paramsDS;
}

BycGLTextureCache *BycSceneManager::getGLTextureCache() {
    return _texCache;
}

BycComponent *BycSceneManager::getComponent(const String &name) {
    auto iter = _comps.find(name);
    if (iter != _comps.end())
        return iter->second;

    // Create it.
    BycComponent *comp = new BycComponent(name);
    _comps.insert(ComponentKV::value_type(name, comp));
    return comp;
}

bool BycSceneManager::destroyComponent(const String &name) {
    auto iter = _comps.find(name);
    if (iter == _comps.end())
        return false;

    delete iter->second;
    _comps.erase(iter);
    return true;
}

BycCamera *BycSceneManager::getCamera(const String &name) {
    auto iter = _cameras.find(name);
    if (iter != _cameras.end())
        return iter->second;

    // Create it.
    BycCamera *cam = new BycCamera(name);
    _cameras.insert(CameraKV::value_type(name, cam));
    return cam;
}

bool BycSceneManager::destroyCamera(const String &name) {
    auto iter = _cameras.find(name);
    if (iter == _cameras.end())
        return false;

    delete iter->second;
    _cameras.erase(iter);
    return true;
}

void BycSceneManager::setCurrentCamera(BycCamera *camera) {
    _currCamera = camera;
}

BycCamera *BycSceneManager::getCurrentCamera() {
    return _currCamera;
}

BycPointLight *BycSceneManager::addPointLight(const String &name) {
    for (BycLight *light : _lights) {
        if (light->getLightType() == BycLight::LightType::POINT && light->getName() == name) {
            assert(false);
        }
    }
    BycPointLight *pointLight = new BycPointLight(name);
    _lights.push_back((BycLight *) pointLight);
    return pointLight;
}

BycDirectionalLight *BycSceneManager::addDirectionalLight(const String &name) {
    for (BycLight       *light : _lights) {
        if (light->getLightType() == BycLight::LightType::DIRECTION && light->getName() == name) {
            assert(false);
        }
    }
    BycDirectionalLight *directionalLight = new BycDirectionalLight(name);
    _lights.push_back((BycLight *) directionalLight);
    return directionalLight;
}

BycSpotLight *BycSceneManager::addSpotLight(const String &name) {
    for (BycLight *light : _lights) {
        if (light->getLightType() == BycLight::LightType::SPOT && light->getName() == name) {
            assert(false);
        }
    }
    BycSpotLight  *spotLight = new BycSpotLight(name);
    _lights.push_back((BycLight *) spotLight);
    return spotLight;
}

const BycSceneManager::LightArr &BycSceneManager::getLights() const {
    return _lights;
}

void BycSceneManager::setAmbientLightColor(const Vec4 &ambientColor) {
    _ambientColor = ambientColor;
}

const Vec4 &BycSceneManager::getAmbientLightColor() const {
    return _ambientColor;
}

void BycSceneManager::destroyComponentKV() {
    auto iter = _comps.begin();
    for (; iter != _comps.end(); ++iter) {
        delete iter->second;
        _comps.erase(iter);
    }
}

void BycSceneManager::destroyCameraKV() {
    auto iter = _cameras.begin();
    for (; iter != _cameras.end(); ++iter) {
        delete iter->second;
        _cameras.erase(iter);
    }
}

void BycSceneManager::drawScene() {
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_ALPHA_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    for (ComponentKV::value_type &pair : _comps) {
        drawComponent(pair.second);
    }
}

void BycSceneManager::drawComponent(BycComponent *comp) {
    for (BycEntity *entity : comp->_entities) {
        drawEntity(entity);
    }
}

void BycSceneManager::drawEntity(BycEntity *entity) {
    for (BycSubEntity *sub : entity->getSubEntityArray()) {
        drawSubEntity(sub);
    }
}

void BycSceneManager::drawSubEntity(BycSubEntity *sub) {
    // Set uniforms data.
    _paramsDS->setModelMatrix(sub->getModelMatrix());
    _paramsDS->setCurrentCamera(_currCamera);

    // Get material.
    BycMaterial *mtl = sub->getMaterial();
    if (mtl == nullptr)
        mtl = sub->getParent()->getMaterial();

    BycPass *pass = mtl->getPass(0);

    pass->updateGLShaderParameters(_paramsDS);

    _renderSystem->_usePass(pass);

    sub->commitData();
    sub->bindData();

    BycRenderOpt opt;
    sub->getRenderOpt(opt);

    _renderSystem->draw(opt, pass);
}


