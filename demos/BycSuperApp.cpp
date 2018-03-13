//
//  BycSuperApp.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/30.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycSuperApp.h"

#include "BycSceneManager.h"
#include "BycCamera.h"

BycSuperApp::BycSuperApp(const String& name, int width, int height) :
BycApp(name, width, height) {
    _window->setMouseClickEvent(this);
    _window->setKeyEvent(this);
    
    // Set scene manager.
    _sceneManager = new BycSceneManager();
    _window->setSceneManager(_sceneManager);
    
    // Get or create camera.
    BycCamera* camera = _sceneManager->getCamera("No.1");
    camera->setPosition(Vec3(0, 2, 5));
    
    // Set current valid camera.
    _sceneManager->setCurrentCamera(camera);
} 

BycSuperApp::~BycSuperApp() {
    _window->setMouseClickEvent(nullptr);
    _window->setKeyEvent(nullptr);
    
    delete _sceneManager;
    _sceneManager = nullptr;
}

void BycSuperApp::initScene() {
}

void BycSuperApp::onMouseClick(int btnType, double x, double y) {
    if (btnType == MOUSE_BUTTON_RIGHT){
        printf("Mouse right click: [%f, %f]\n", x, y);
    }
}

void BycSuperApp::onKeyClick(int key, int scanCode, int action, int mods) {
    BycCamera* currCamera = _sceneManager->getCurrentCamera();
    Vec3 pos = currCamera->getPosition();
    
    float step = 0.5f;
    switch(action) {
        case GLFW_PRESS:
        case GLFW_REPEAT:
        {
            if (key == GLFW_KEY_W)
                currCamera->setPosition(pos + Vec3(0, 0, -step));
            else if (key == GLFW_KEY_S)
                currCamera->setPosition(pos + Vec3(0, 0, step));
            else if (key == GLFW_KEY_A)
                currCamera->setPosition(pos + Vec3(-step, 0, 0));
            else if (key == GLFW_KEY_D)
                currCamera->setPosition(pos + Vec3(step, 0, 0));
            else if (key == GLFW_KEY_Q)
                currCamera->setPosition(pos + Vec3(0, step, 0));
            else if (key == GLFW_KEY_Z)
                currCamera->setPosition(pos + Vec3(0, -step, 0));
            else if (key == GLFW_KEY_LEFT)
                currCamera->setOrientation(0, 0, glm::radians(1.0f));
            else if (key == GLFW_KEY_RIGHT)
                currCamera->setOrientation(0, -glm::radians(1.0f), 0);
            else if (key == GLFW_KEY_UP)
                currCamera->setOrientation(glm::radians(1.0f), 0, 0);
            else if (key == GLFW_KEY_DOWN)
                currCamera->setOrientation(-glm::radians(1.0f), 0, 0);
        } break;
        default:break;
    }
}

