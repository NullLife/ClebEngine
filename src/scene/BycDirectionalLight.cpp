//
//  BycDirectionalLight.cpp
//  BycRun
//
//  Created by FengMap on 2018/3/5.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "./BycDirectionalLight.h"

BycDirectionalLight::BycDirectionalLight(const String& name) :
BycLight(BycLight::LightType::DIRECTION, name),
_dir(Vec3(0, 1.0f, 0)) {
    _intensity = 1.0f;
    _diffuseColor = _specularColor = Vec4(1.0f);
    _atten = Vec4(1.0, 1.0, 0.09, 0.032);
} 

BycDirectionalLight::~BycDirectionalLight() {
}

void BycDirectionalLight::setDirection(const Vec3& dir) {
    _dir = dir;
}

const Vec3& BycDirectionalLight::getDirection() const {
    return _dir;
}
