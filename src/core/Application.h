//
// Created by jakub on 14.02.2026.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <memory>
#include "Window.h"


class Application {
public:
    Application(int width, int height, const std::string& title);
    void run();
    // TODO: InputManager
private:
    // Timing (FPS)
    float deltaTime, lastFrame;

    // Window
    std::shared_ptr<Window> window;
    std::string windowTitle;
    bool lockedCursor, tabPressed;

    void createWindow(int width, int height, const std::string& title);
    void calculateFPS();

    // Window callback functions
    void mouseCallback(double xpos, double ypos);
    void frameBufferSizeCallback(int width, int height);
    void scrollCallback(double xoffset, double yoffset);
    void processInput();
};



#endif //APPLICATION_H
