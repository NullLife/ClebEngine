//
//  BycMaterial.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycMaterial.h"

#include "BycPass.h"

BycMaterial::BycMaterial() :
_name(""),
_specularIntensity(1.0f), _shininess(128.0f),
_defaultColor(0.5, 0.5, 0.5, 1.0) {
} 

BycMaterial::~BycMaterial() {
    
}

void BycMaterial::setSpecularIntensity(float intensity) {
    _specularIntensity = intensity;
}

float BycMaterial::getSpecularIntensity() {
    return _specularIntensity;
}

void BycMaterial::setShininess(float shininess) {
    _shininess = shininess;
}

float BycMaterial::getShininess() {
    return _shininess;
}

BycPass* BycMaterial::createPass(const String& name) {
    for (BycPass* pass : _passes) {
        if (pass->getName() == name) {
            printf("BycMaterial::createPass==> %s\n%s\n", name.c_str(), "Can't create the pass.");
            assert(false);
        }
    }
    
    BycPass* pass = new BycPass();
    pass->setName(name);
    pass->setParent(this);
    
    _passes.push_back(pass);
    
    return pass;
}

int BycMaterial::addImage(const String& image) {
    auto iter = std::find(_images.begin(), _images.end(), image);
    if (iter != _images.end()) {
        return -1;
    }
    _images.push_back(image);
    return (int)_images.size()-1;
}

const String& BycMaterial::getImage(const int index) const {
    return _images[index];
}

BycPass* BycMaterial::getPass(int index) {
    return _passes[index];
}

