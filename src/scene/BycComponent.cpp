//
//  BycComponent.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycComponent.h"
#include "BycEntity.h"

BycComponent::BycComponent(const String& name) : _name(name) {

}

BycComponent::~BycComponent() {
    clearEntities();
}

const String& BycComponent::getUniqueName() const {
    return _name;
}

unsigned int BycComponent::addEntity(BycEntity *entity) {
    unsigned int index = (unsigned int) _entities.size();
    _entities.push_back(entity);
    return index;
}


BycEntity *BycComponent::removeEntity(unsigned int index) {
    assert(index >=0 && index < _entities.size());
    return *_entities.erase(_entities.begin() + index);
}


bool BycComponent::removeEntity(BycEntity *entity) {
    EntityArr::iterator iter = std::find(_entities.begin(), _entities.end(), entity);
    if (iter == _entities.end())
        return false;
    
    _entities.erase(iter);
    
    return true;
}


bool BycComponent::destroyEntity(unsigned int index) {
    BycEntity *e = removeEntity(index);
    delete e;
    e = nullptr;
    return true;
}


bool BycComponent::destroyEntity(BycEntity *entity) {
    if (!removeEntity(entity))
        return false;
    
    delete entity;
    entity = nullptr;
    
    return true;
}

void BycComponent::clearEntities() {
    _entities.clear();
    _entities.shrink_to_fit();
}

