//
//  BycParamsDataSource.h
//  BycRun
//
//  Created by FengMap on 2018/1/27.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycParamsDataSource_h
#define BycParamsDataSource_h

#include "BycDefinitions.h"

class BycCamera;

class BycParamsDataSource {
public:
    BycParamsDataSource();  
    ~BycParamsDataSource();
    
    void setCurrentCamera(BycCamera* camera);
    
    void setModelMatrix(const Mat4& m);
    const Mat4& getModelMatrix();
    
    const Mat4& getViewMatrix();
    const Mat4& getProjectionMatrix();
      
private:
    mutable Mat4 _modelMatrix;

    BycCamera* _currCamera;
};

#endif /* BycParamsDataSource_h */
