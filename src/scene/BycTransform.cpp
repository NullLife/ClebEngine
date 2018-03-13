//
//  BycTransform.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycTransform.h"

BycTransform::BycTransform() :
    _changed(true),
    _postion(Vec3(0)),
    _distance(0, 0, 0), _scale(1.0, 1.0, 1.0) {
    _orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
    _matrix = glm::mat4(1.0);
} 

BycTransform::~BycTransform() {
}

void BycTransform::setPosition(const Vec3& pos) {
    _postion = pos;
    _distance = _postion;
    _changed = true;
}

void BycTransform::move(const Vec3& distance) {
    _distance = distance;
    _postion += distance;
    _changed = true;
}

void BycTransform::setScale(const Vec3& scale) {
    _scale = scale;
    _changed = true;
}

void BycTransform::setPitch(float rad) {
    _orientation = glm::rotate(_orientation, -rad, AXIS_Y);
    _changed = true;
}

void BycTransform::setYaw(float rad) {
    _orientation = glm::rotate(_orientation, -rad, AXIS_X);
    _changed = true;
}

void BycTransform::setRoll(float rad) {
    _orientation = glm::rotate(_orientation, -rad, AXIS_Z);
    _changed = true;
}

void BycTransform::setRotate (Quaternion quat) {
    _orientation = quat;
    _changed = true;
}

const Mat4& BycTransform::getMatrix() {
    _update();
    return _matrix;
}

void BycTransform::_update() {
    if (!_changed)
        return;
    
    // Translate
    _matrix = glm::translate(_matrix, _distance);
    
    // Rotate
    _matrix *= glm::mat4_cast(_orientation);
    
    // Scale
    _matrix = glm::scale(_matrix, _scale);
    
    // Reset
    _scale = Vec3(1.0, 1.0, 1.0);
    _orientation = Quaternion(1.0, 0, 0, 0);
    _distance = Vec3(0, 0, 0);
    
    _changed = false;
}
