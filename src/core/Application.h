//
// Created by jakub on 14.02.2026.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <memory>

#include "InputManager.h"
#include "Window.h"
#include "../graphics/Renderer.h"



class Application {
public:
    Application(int width, int height, const std::string& title);
    void run();
    // TODO: InputManager
private:
    // Timing (FPS)
    float deltaTime, lastFrame;

    // Game
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<World> world;
    std::shared_ptr<InputManager> input;

    // Window
    std::shared_ptr<Window> window;
    std::string windowTitle;

    void createWindow(int width, int height, const std::string& title);
    void calculateFPS();

    // Window callback functions
    void mouseCallback(double xPos, double yPos);
    void scrollCallback(double xOffset, double yOffset);
    void framebufferSizeCallback(int width, int height);
};



#endif //APPLICATION_H
