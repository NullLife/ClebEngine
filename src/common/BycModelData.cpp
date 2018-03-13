//
//  BycModelData.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/30.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycModelData.h"

BycModelData::BycModelData() {

} 

BycModelData::~BycModelData() {
    auto iter = _data.begin();
    while (iter != _data.end()) {
        
        delete *iter;
        
        ++iter;
    }
    
    _data.clear();
    _data.shrink_to_fit();
}

void BycModelData::_addChildModel(ChildModel* model) {
    _data.push_back(model);
}

const Vector<BycModelData::ChildModel*>& BycModelData::getData() {
    return _data;
}
