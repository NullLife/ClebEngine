//
//  BycCamera.h
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycCamera_h
#define BycCamera_h

#include "BycFrustum.h"

class BycSceneManager;

class BycCamera : public BycFrustum {
    friend class BycSceneManager;
public:
    const String& getUniqueName() const;
    
    void setPosition(const Vec3& position);
    const Vec3& getPosition() const;
    
    void setTargetPosition(const Vec3& targetPosition);
    const Vec3& getTargetPosition() const;
    
    void setUpDirection(const Vec3& rightDir);
    const Vec3& getUpDirection() const;
    
    void setOrientation(const Quaternion& orientation);
    const Quaternion& getOrientation() const;
    
    /**
     Picth: The rad of rotation around Y axis.
     Yaw: The rad of rotation around X axis.
     Roll: The rad of rotation around Z axis.
     */
    void setOrientation(float pitch, float yaw, float roll);
    
    const Mat4& getViewMatrix();
    
    String toString();
    
private:
    /// The name is unique for a camera.
    BycCamera(const String& name);
    ~BycCamera();
    
    void update();
    
    String _name;
    
    Vec3 _position;
    Vec3 _targetPosition;
    Vec3 _upDir;
    
    Quaternion _orientation;
    
    Mat4 _viewMatrix;
    
    bool _needUpdateView;
};

#endif /* BycCamera_h */
