//
//  BycApp.h
//  BycRun
//
//  Created by FengMap on 2017/12/28.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycApp_h
#define BycApp_h

#include "BycWindow.h"

class BycApp {
public:
    BycApp(const String& name, int width = 800, int height = 600);
    virtual ~BycApp();
    
    virtual void initScene();
    void running();
    
protected:
    GameWindow* _window;
};

#endif /* BycApp_h */
