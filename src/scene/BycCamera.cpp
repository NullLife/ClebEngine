//
//  BycCamera.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycCamera.h"

BycCamera::BycCamera(const String& name) : BycFrustum(),
_name(name),
_needUpdateView(true),
_position(0.0f, 0.0f, 5.0f), _targetPosition(0.0f, 0.0f, 0.0f), _upDir(0.0f, 1.0f, 0.0f) {
    _orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
} 

BycCamera::~BycCamera() {
}

const String& BycCamera::getUniqueName() const {
    return _name;
}


void BycCamera::setPosition(const Vec3& position) {
    _position = position;
    _needUpdateView = true;
}
const Vec3& BycCamera::getPosition() const {
    return _position;
}

void BycCamera::setTargetPosition(const Vec3& targetPosition) {
    _targetPosition = targetPosition;
    _needUpdateView = true;
}
const Vec3& BycCamera::getTargetPosition() const {
    return _targetPosition;
}

void BycCamera::setUpDirection(const Vec3& upDir) {
    _upDir = upDir;
    _needUpdateView = true;
}
const Vec3& BycCamera::getUpDirection() const {
    return _upDir;
}

void BycCamera::setOrientation(const Quaternion& orientation) {
    _orientation = orientation;
    _needUpdateView = true;
}
const Quaternion& BycCamera::getOrientation() const {
    return _orientation;
}

void BycCamera::setOrientation(float pitch, float yaw, float roll) {
    _orientation = glm::rotate(_orientation, -pitch, AXIS_Y);
    _orientation = glm::rotate(_orientation, -yaw, AXIS_X);
    _orientation = glm::rotate(_orientation, -roll, AXIS_Z);
    _needUpdateView = true;
}

const Mat4& BycCamera::getViewMatrix() {
    update();
    return _viewMatrix;
}

String BycCamera::toString() {
    return std::to_string(_position.x) + ", " +std::to_string(_position.y) + ", " +std::to_string(_position.z);
}

void BycCamera::update() {
    if (!_needUpdateView)
        return;
    
    // Rotate
    Mat3 rotM;
    rotM = glm::mat3_cast(_orientation);
    
    Vec3 lookDir = rotM * (_targetPosition - _position);
    lookDir = glm::normalize(lookDir);
    
    _upDir = rotM * _upDir;
    _upDir = glm::normalize(_upDir);
    
    Vec3 camRight = glm::cross(lookDir, _upDir);
    camRight = glm::normalize(camRight);

    _upDir = glm::cross(camRight, lookDir);
    _upDir = glm::normalize(_upDir);
    
    _viewMatrix = glm::lookAt(_position, _position + lookDir, _upDir);
    
    // Returns euler angles, yitch as x, yaw as y, roll as z.
//    _pitch = glm::pitch(_orientation);
//    _yaw = glm::yaw(_orientation);
//    _roll = glm::roll(_orientation);
    
    _needUpdateView = false;
}
