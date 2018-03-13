//
//  BycParamsDataSource.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/27.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycParamsDataSource.h"
#include "BycCamera.h"

BycParamsDataSource::BycParamsDataSource() :
_currCamera(nullptr) {
} 

BycParamsDataSource::~BycParamsDataSource() {
}

void BycParamsDataSource::setCurrentCamera(BycCamera* camera) {
    _currCamera = camera;
}

void BycParamsDataSource::setModelMatrix(const Mat4& m) {
    _modelMatrix = m;
}

const Mat4& BycParamsDataSource::getModelMatrix() {
    return _modelMatrix;
}

const Mat4& BycParamsDataSource::getViewMatrix() {
    return _currCamera->getViewMatrix();
}

const Mat4& BycParamsDataSource::getProjectionMatrix() {
    return _currCamera->getProjectionMatrix();
}

