//
//  BycSpotLight.cpp
//  BycRun
//
//  Created by FengMap on 2018/3/5.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycSpotLight.h"

BycSpotLight::BycSpotLight(const String& name) :
BycLight(BycLight::LightType::SPOT, name),
_cutoff(0.5f) {
    _intensity = 1.0f;
    _diffuseColor = _specularColor = Vec4(1.0f);
    _atten = Vec4(1.0, 1.0, 0.09, 0.032);
} 

BycSpotLight::~BycSpotLight() {
}

void BycSpotLight::setCutoff(float rad) {
    _cutoff = rad;
}

const float BycSpotLight::getCutoff() const {
    return _cutoff;
}
