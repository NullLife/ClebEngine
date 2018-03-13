//
//  BycWindow.cpp
//  BycRun
//
//  Created by FengMap on 2017/12/27.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#include "BycWindow.h"

#include "BycSceneManager.h"

GameWindow::GameWindow(const String& name, int width, int height) :
_name(name),
_width(width),
_height(height),
_sceneManager(nullptr),
_clearColor(Vec3(0.0f, 0.0f, 0.0f)),
_clearDepth(1.0f),
_mouseClickEvent(nullptr), _ketEvent(nullptr) {
    initWindow();
}

GameWindow::~GameWindow() {
    glfwDestroyWindow(_window);
}

const String &GameWindow::getName() const {
    return _name;
}

const int GameWindow::getWidth() const {
    return _width;
}

const int GameWindow::getHeight() const {
    return _height;
}

void GameWindow::setSceneManager(BycSceneManager* manager) {
    _sceneManager = manager;
}

BycSceneManager* GameWindow::getSceneManager() {
    return _sceneManager;
}

void GameWindow::running() {
    while (!glfwWindowShouldClose(_window)) {
        // Render here.
        drawScene();
        
        glfwSwapBuffers(_window);
        
        // Poll for and process events
        glfwPollEvents();
    }
}

void GameWindow::setMouseClickEvent(BycMouseClikEvent* event) {
    _mouseClickEvent = event;
}

BycMouseClikEvent* GameWindow::getMouseClickEvent() {
    return _mouseClickEvent;
}

void GameWindow::setKeyEvent(BycKeyEvent* event) {
    _ketEvent = event;
}
BycKeyEvent* GameWindow::getKeyEvent() {
    return _ketEvent;
}

void GameWindow::initWindow() {
    // Initialize GLFW.
    int r = glfwInit();
    if (r != GL_TRUE)
        return;
    
    // OpenGL Version.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    // Mac need it.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Use core profile.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);

//    glfwSwapInterval(1);
    
    // Create window.
    _window = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);
    if (!_window) {
        glfwTerminate();
        return;
    }
    
    // Make the window's context current.
    glfwMakeContextCurrent(_window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        printf("GameWindow::initWindow [%s]", "Fail to initialize glew!");
    
    if (glewIsSupported("GL_VERSION_4_1"))
        printf("\n========== [%s] ==========\n", "OpenGL 4.1");
    else
        printf("\n========== [%s] ==========\n", "OpenGL 4.1 not supported");
    
    // Set events.
    setEventCallbacks();
    
    // Share window's pointer.
    glfwSetWindowUserPointer(_window, (void *) this);
    
    // Get version info.
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version  = glGetString(GL_VERSION);
    printf("%s: %s\n", "Renderer", renderer);
    printf("%s: %s\n", "Version" , version);
    
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(_window, &frameWidth, &frameHeight);
    glViewport(0, 0, frameWidth, frameHeight);
    printf("FrameBuffer: [%d, %d]\n", frameWidth, frameHeight);
    printf("%s\n\n", "======================");
}

void GameWindow::setEventCallbacks() {
    glfwSetMouseButtonCallback(_window, mouseButtonCallback);
    glfwSetKeyCallback(_window, keyCallback);
}

void GameWindow::drawScene() {
    CHECK_GL_ERROR(glClearBufferfv(GL_COLOR, 0, &_clearColor[0]));
    CHECK_GL_ERROR(glClearBufferfv(GL_DEPTH, 0, &_clearDepth));
    
    if (_sceneManager == nullptr)
        return;
    
    // Start render scene.
    _sceneManager->drawScene();
}


void GameWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    GameWindow* myWindow = reinterpret_cast<GameWindow *> (glfwGetWindowUserPointer(window));
    BycMouseClikEvent* event = myWindow->getMouseClickEvent();
    if (!event)
        return;
    
    int btnTye = button == GLFW_MOUSE_BUTTON_RIGHT ? MOUSE_BUTTON_RIGHT : MOUSE_BUTTON_LEFT;
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if (action == GLFW_PRESS)
        event->onMouseClick(btnTye, x, y);
}

void GameWindow::keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    GameWindow *myWindow  = reinterpret_cast<GameWindow *>(glfwGetWindowUserPointer(window));
    BycKeyEvent *event = myWindow->getKeyEvent();
    if (!event)
        return;
    
    event->onKeyClick(key, scanCode, action, mods);
}


