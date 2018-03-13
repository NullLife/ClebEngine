//
//  BycDeferredLightApp.h
//  BycRun
//
//  Created by FengMap on 2018/1/30.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycDeferredLightApp_h
#define BycDeferredLightApp_h

#include "BycSuperApp.h"

class BycEntity;

class BycDeferredLightApp : public BycSuperApp {
public:
    struct EntityMtlThings {
        const String _passName;
        const String _verShaderName;
        const String _fragShaderName;
        
        Vector<String> _images;
    };
    
    BycDeferredLightApp(const String& name);
    ~BycDeferredLightApp();
      
private:
    void initScene();
    BycEntity* loadEntity(const String& name, EntityMtlThings things);
    void initMaterial(BycEntity* entity, EntityMtlThings things);
};

#endif /* BycDeferredLightApp_h */
