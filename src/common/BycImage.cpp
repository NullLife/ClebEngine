//
//  BycImage.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycImage.h"
#include "BycIOUtils.h"

#include <SOIL.h>

BycImage::BycImage() :
_originWidth(0), _originHeight(0),
_rqWidth(0), _rqHeight(0),
_buffer(nullptr) {
} 

BycImage::~BycImage() {
    if (_buffer != nullptr) {
        delete _buffer;
        _buffer = nullptr;
    }
}

void BycImage::setWidth(int width) {
    _rqWidth = width;
}

void BycImage::setHeight(int height) {
    _rqHeight = height;
}

const int BycImage::getWidth() const {
    return _rqWidth;
}

const int BycImage::getHeight() const {
    return _rqHeight;
}

const bool BycImage::loadImage(const std::string& path) {
    _buffer = BycIOUtils::readImage(path, &_originWidth, &_originHeight, &_channels, SOIL_LOAD_RGBA);
    _rqWidth = _originHeight;
    _rqHeight = _originHeight;
    return _buffer != nullptr;
}

const int BycImage::getChannels() const {
    return 0;
}

const unsigned char* BycImage::getBuffer() {
    return _buffer;
}
