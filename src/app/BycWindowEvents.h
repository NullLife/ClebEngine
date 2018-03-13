//
//  BycWindowEvents.h
//  BycRun
//
//  Created by FengMap on 2017/12/30.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycWindowEvents_h
#define BycWindowEvents_h

const int MOUSE_BUTTON_RIGHT = 1;
const int MOUSE_BUTTON_LEFT = 2;

class BycMouseClikEvent {
public:
    virtual void onMouseClick(int btnType, double x, double y) = 0;
};

class BycKeyEvent {
public:
    virtual void onKeyClick(int key, int scanCode, int action, int mods) = 0;
};

#endif /* BycWindowEvents_hpp */
