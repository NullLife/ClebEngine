//
//  BycDirectionalLight.h
//  BycRun
//
//  Created by FengMap on 2018/3/5.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycDirectionalLight_h
#define BycDirectionalLight_h

#include "./BycLight.h"

class BycDirectionalLight : public BycLight {
public:
    BycDirectionalLight(const String& name);  
    ~BycDirectionalLight();
    
    /// Set the direction of light.
    void setDirection(const Vec3& dir);
    const Vec3& getDirection() const;
    
private:  
    Vec3 _dir;
};

#endif /* BycDirectionalLight_h */
