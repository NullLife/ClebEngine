//
//  BycWindow.h
//  BycRun
//
//  Created by FengMap on 2017/12/27.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycWindow_h
#define BycWindow_h

#include "BycDefinitions.h"
#include "glfw3.h"

#include "BycWindowEvents.h"

class BycSceneManager;

/** Game Window.
 */
class GameWindow {
public:
    GameWindow(const String& name, int width, int height);
    ~GameWindow();
public:
    const String& getName() const;
    
    const int getWidth() const;
    const int getHeight() const;
    
    void setSceneManager(BycSceneManager* manager);
    BycSceneManager* getSceneManager();
    
    void running();
    
    void setMouseClickEvent(BycMouseClikEvent* event);
    BycMouseClikEvent* getMouseClickEvent();
    
    void setKeyEvent(BycKeyEvent* event);
    BycKeyEvent* getKeyEvent();
    
private:
    void initWindow();
    void setEventCallbacks();
    void drawScene();
    
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);
    
private:
    String _name;
    
    int _width;
    int _height;
    
    GLFWwindow *_window;
    Vec3 _clearColor;
    float _clearDepth;
    
    BycSceneManager* _sceneManager;
    
    BycMouseClikEvent* _mouseClickEvent;
    BycKeyEvent* _ketEvent;
};

#endif /* BycWindow_h */
