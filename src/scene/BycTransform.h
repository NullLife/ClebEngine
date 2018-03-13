//
//  BycTransform.h
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycTransform_h
#define BycTransform_h

#include "BycDefinitions.h"

class BycTransform {
public:
    BycTransform();  
    ~BycTransform();
    
    void setPosition(const Vec3& pos);
    
    /// Move.
    void move(const Vec3& distance);
    
    /// Scale.
    void setScale(const Vec3& scale);
    
    /// Rotate.
    void setPitch(float rad);
    void setYaw(float rad);
    void setRoll(float rad);
    void setRotate (Quaternion quat);

    const Mat4& getMatrix();
      
private:
    void _update();
    
    Vec3 _postion;
    Vec3 _distance;
    Vec3 _scale;
    Quaternion _orientation;
    
    Mat4 _matrix;
    
    bool _changed;
};

#endif /* BycTransform_h */
