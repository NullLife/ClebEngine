//
//  BycFrustum.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "./BycFrustum.h"

BycFrustum::BycFrustum() :
_projType(PERSPECTIVE),
_aspectRatio(1.333f), _fovy(45.0f), _zNear(0.1f), _zFar(200.0f),
_left(-10), _right(10), _top(10), _bottom(-10),
_needUpdateFrustum(true) {
}

BycFrustum::~BycFrustum() {
 	
}

void BycFrustum::setProjectionType(BycFrustum::ProjectionType type) {
    _projType = type;
    _needUpdateFrustum = true;
}


const BycFrustum::ProjectionType BycFrustum::getProjectionType() const {
    return _projType;
}

void BycFrustum::setFrustum(float fovy, float aspectRatio, float nearDist, float farDist) { 
    _fovy = fovy;
    _aspectRatio = aspectRatio;
    _zNear = nearDist;
    _zFar = farDist;
    _needUpdateFrustum = true;
}

void BycFrustum::setFrustumExtends(float left, float right, float bottom, float top) { 
    _left = left;
    _right = right;
    _bottom = bottom;
    _top = top;
    _needUpdateFrustum = true;
}

const Mat4& BycFrustum::getProjectionMatrix() {
    _updateFrustum();
    return _projMatrix;
}

void BycFrustum::_updateFrustum() {
    if (!_needUpdateFrustum)
        return;
    
    if (_projType == ProjectionType::PERSPECTIVE) {
#ifdef MATH_GLM
        _projMatrix = glm::perspective(_fovy, _aspectRatio, _zNear, _zFar);
#else
        //_projMatrix = float4x4::OpenGLPerspProjRH(_zNear, _zFar, float horizontalViewportSize, float verticalViewportSize);
#endif
    }
    else {
        _projMatrix = glm::ortho(_left, _right, _bottom, _top, _zNear, _zFar);
    }
    
    _needUpdateFrustum = false;
}


