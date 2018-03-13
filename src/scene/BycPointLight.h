//
//  BycPointLight.h
//  BycRun
//
//  Created by FengMap on 2018/3/4.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycPointLight_h
#define BycPointLight_h

#include "./BycLight.h"

class BycPointLight : public BycLight {
public:
    BycPointLight(const String& name);
    ~BycPointLight();
    
    /// Set position.
    void setPosition(const Vec3& pos);
    const Vec3& getPosition() const;
      
private:  
    Vec3 _position;
};

#endif /* BycPointLight_h */
