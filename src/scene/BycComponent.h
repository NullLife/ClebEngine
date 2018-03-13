//
//  BycComponent.h
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycCommponent_h
#define BycCommponent_h

#include "BycDefinitions.h"

class BycEntity;
class BycSceneManager;

class BycComponent {
    friend class BycSceneManager;
public:
    typedef Vector<BycEntity*> EntityArr;
    
    const String& getUniqueName() const;
    
    virtual unsigned int addEntity(BycEntity* entity);
    virtual BycEntity* removeEntity(unsigned int index);
    virtual bool removeEntity(BycEntity* entity);
    virtual bool destroyEntity(unsigned int index);
    virtual bool destroyEntity(BycEntity* entity);
    
    void clearEntities();
      
protected:
    BycComponent(const String& name);
    virtual ~BycComponent();
    
    String _name;
    EntityArr _entities;
};

#endif /* BycCommponent_h */
