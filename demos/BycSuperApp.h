//
//  BycSuperApp.h
//  BycRun
//
//  Created by FengMap on 2018/1/30.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycSuperApp_h
#define BycSuperApp_h

#include "BycApp.h"

class BycSuperApp : public BycApp, public BycMouseClikEvent, public BycKeyEvent {
public:
    BycSuperApp(const String& name, int width =800, int height=600);
    virtual ~BycSuperApp();  
      
protected:  
    virtual void initScene();
    virtual void onMouseClick(int btnType, double x, double y);
    virtual void onKeyClick(int key, int scanCode, int action, int mods);
    
    BycSceneManager* _sceneManager;
};

#endif /* BycSuperApp_h */
