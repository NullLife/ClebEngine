//
//  BycPointLight.cpp
//  BycRun
//
//  Created by FengMap on 2018/3/4.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "./BycPointLight.h"

BycPointLight::BycPointLight(const String& name) :
BycLight(BycLight::LightType::POINT, name),
_position(Vec3(0)) {
    _intensity = 1.0f;
    _diffuseColor = _specularColor = Vec4(1.0f);
    _atten = Vec4(1.0, 1.0, 0.09, 0.032);
} 

BycPointLight::~BycPointLight() {
}

void BycPointLight::setPosition(const Vec3& pos) {
    _position = pos;
}

const Vec3& BycPointLight::getPosition() const {
    return _position;
}
