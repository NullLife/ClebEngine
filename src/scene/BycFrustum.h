//
//  BycFrustum.h
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycFrustum_h
#define BycFrustum_h

#include "BycDefinitions.h"

class BycFrustum {
public:
    enum ProjectionType
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };
    
    /** Worldspace clipping planes.
     */
    enum FrustumPlane
    {
        NEAR   = 0,
        FAR    = 1,
        LEFT   = 2,
        RIGHT  = 3,
        TOP    = 4,
        BOTTOM = 5
    };
    
    BycFrustum();  
    virtual ~BycFrustum();
    
    void setProjectionType(ProjectionType type);
    const ProjectionType getProjectionType() const;
    
    // Perspective
    void setFrustum(float fovy, float aspectRatio, float nearDist, float farDist);

    // Orthograhic
    void setFrustumExtends(float left, float right, float bottom, float top);
    
    const Mat4& getProjectionMatrix();
    
private:
    void _updateFrustum();

protected:
    ProjectionType _projType;
    
    float _fovy;
    float _aspectRatio;
    float _zNear;
    float _zFar;
    
    float _left;
    float _top;
    float _right;
    float _bottom;
    
    Mat4 _projMatrix;
    
    bool _needUpdateFrustum;
};

#endif /* BycFrustum_h */
