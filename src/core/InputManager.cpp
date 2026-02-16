//
// Created by jakub on 16.02.2026.
//

#include "InputManager.h"

#include <iostream>

InputManager::InputManager(World &world, Window &window, Renderer &renderer):
    lastX(0), lastY(0), firstMouse(true),
    world(world), window(window), renderer(renderer),
    lockedCursor(true),
    tabPressed(false), f1Pressed(false), f2Pressed(false){}

void InputManager::mouseCallback(double xPosIn, double yPosIn) {
    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    // Calculate offset
    if (firstMouse || !lockedCursor) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    if (!lockedCursor)
        return;

    float offsetX = xPos - lastX;
    float offsetY = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    world.processMouseMovement(offsetX, offsetY);
}

void InputManager::scrollCallback(double xOffset, double yOffset) {
    world.processScroll(yOffset);
}

void InputManager::processInput(float deltaTime) {
    GLFWwindow* window = this->window.getGLFWwindow();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        world.processMovement(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        world.processMovement(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        world.processMovement(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        world.processMovement(RIGHT, deltaTime);

    // Wireframe toggle
    int f1State = glfwGetKey(window, GLFW_KEY_F1);
    if (f1State == GLFW_PRESS && !f1Pressed) {
        f1Pressed = true;
        renderer.toggleWireframe();
    } else if (f1State == GLFW_RELEASE && f1Pressed) {
        f1Pressed = false;
    }

    // Physics toggle
    int f2State = glfwGetKey(window, GLFW_KEY_F2);
    if (f2State == GLFW_PRESS && !f2Pressed) {
        f2Pressed = true;
        world.togglePhysics();
    } else if (f2State == GLFW_RELEASE && f2Pressed) {
        f2Pressed = false;
    }

    // Mouse lock toggle
    int tabState = glfwGetKey(window, GLFW_KEY_TAB);
    if (tabState == GLFW_PRESS && !tabPressed) {
        tabPressed = true;
        lockedCursor = !lockedCursor;
        glfwSetInputMode(window, GLFW_CURSOR, lockedCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    } else if (tabState == GLFW_RELEASE && tabPressed) {
        tabPressed = false;
    }
}