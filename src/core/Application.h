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

    void mouseCallback(double xpos, double ypos);
    void frameBufferSizeCallback(int width, int height);
    void scrollCallback(double xoffset, double yoffset);
    // TODO: input callback?
private:
    // Timing (FPS)
    float deltaTime, lastFrame;

    std::shared_ptr<Window> window;
    std::string windowTitle;

    void createWindow(int width, int height, const std::string& title);
    void calculateFPS();
};



#endif //APPLICATION_H
