//
//  BycDrawable.h
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycDrawable_h
#define BycDrawable_h

#include "BycDefinitions.h"

class BycMesh;
class BycMaterial;
class BycRenderOpt;

class BycDrawable {
public:
    BycDrawable();  
    virtual ~BycDrawable();
    
    virtual const Mat4& getModelMatrix() = 0;
    
    virtual BycMaterial* getMaterial() = 0;
    virtual BycMesh* getMesh() = 0;
    virtual void getRenderOpt(BycRenderOpt& opt) = 0;
    
    virtual void commitData() = 0;
    virtual void bindData() = 0;
};

#endif /* BycDrawable_h */
