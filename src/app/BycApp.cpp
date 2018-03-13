//
//  BycApp.cpp
//  BycRun
//
//  Created by FengMap on 2017/12/28.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#include "BycApp.h"


BycApp::BycApp(const std::string &name, int width, int height) :
_window(new GameWindow(name, width, height)) {
}

BycApp::~BycApp() {
    delete _window;
    _window = nullptr;
}

void BycApp::initScene() {
}

void BycApp::running() {
    initScene();
    _window->running();
}

