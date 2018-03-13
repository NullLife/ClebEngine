//
//  BycLight.cpp
//  BycRun
//
//  Created by FengMap on 2018/3/4.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycLight.h"

BycLight::BycLight(const LightType type, const String& name) : _type(type), _name(name) {
} 

BycLight::~BycLight() {
}

const String& BycLight::getName() const {
    return _name;
}

const BycLight::LightType BycLight::getLightType() const {
    return _type;
}

void BycLight::setIntensity(float intensity) {
    _intensity = intensity;
}
const float BycLight::getIntensity() const {
    return _intensity;
}

void BycLight::setDiffuseColor(const Vec4& color) {
    _diffuseColor = color;
}

const Vec4& BycLight::getDiffuseColor() const {
    return _diffuseColor;
}

void BycLight::setSpecularColor(const Vec4& color) {
    _specularColor = color;
}

const Vec4& BycLight::getSpecularColor() const {
    return _specularColor;
}

void BycLight::setAttenuation(float constant, float linear, float quadratic, float range) {
    _atten = Vec4(constant, linear, quadratic, range);
}

const Vec4& BycLight::getAttenuation() const {
    return _atten;
}

const float BycLight::getAttenuationRange() const {
    return _atten.w;
}

const float BycLight::getAttenuationConstant() const {
    return _atten.x;
}

const float BycLight::getAttenuationLinear() const {
    return _atten.y;
}

const float BycLight::getAttenuationQuadric() const {
    return _atten.z;
}

