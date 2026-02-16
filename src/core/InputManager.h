//
// Created by jakub on 16.02.2026.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "Window.h"
#include "World.h"
#include "../graphics/Renderer.h"


class InputManager {
public:
    InputManager(World& world, Window& window, Renderer& renderer);

    // Window callback functions
    void mouseCallback(double xPosIn, double yPosIn);
    void scrollCallback(double xOffset, double yOffset);
    void processInput(float deltaTime);

private:
    // Mouse movement
    float lastX, lastY;
    bool firstMouse;

    World& world;
    Window& window;
    Renderer& renderer;

    bool lockedCursor, tabPressed, f1Pressed, f2Pressed;
};



#endif //INPUTMANAGER_H
