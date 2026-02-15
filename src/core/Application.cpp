//
// Created by jakub on 14.02.2026.
//

#include "Application.h"
#include "GLFW/glfw3.h"
#include <iostream>

Application::Application(int width, int height, const std::string& title):
    deltaTime(0.0f), lastFrame(0.0f),
    windowTitle(title), lockedCursor(true), tabPressed(false) {
    createWindow(width, height, title);

    // Create instances:
    // inputmanager - window reference
    // renderer - world reference, camera reference
    // world - idk yet

}

void Application::run() {
    while (!window->shouldClose()) {
        calculateFPS();

        processInput();

        // Update game state
        // update();

        // Rendering
        // render();

        glfwPollEvents();
    }
}

void Application::createWindow(int width, int height, const std::string& title) {
    window = std::make_shared<Window>(width, height, title);
    window->setUp();

    // Set static GLFW callbacks to class functions
    window->setMouseCallback([this](double xpos, double ypos) {
        this->mouseCallback(xpos, ypos);
    });
    window->setFrameBufferSizeCallback([this](int width, int height) {
        this->frameBufferSizeCallback(width, height);
    });
    window->setScrollCallback([this](double xoffset, double yoffset) {
        this->scrollCallback(xoffset, yoffset);
    });

}

void Application::calculateFPS() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    int fps = static_cast<int>(1.0f / deltaTime);
    glfwSetWindowTitle(window->getGLFWwindow(), (windowTitle + " - FPS: " + std::to_string(fps)).c_str());
}

// TODO: temp function, will be moved to Input
void Application::mouseCallback(double xpos, double ypos) {
    std::cout<<"Mouse callback: " << xpos << ", " << ypos << std::endl;
}

// TODO: temp function, will be moved to Input
void Application::frameBufferSizeCallback(int width, int height) {
    std::cout << "Framebuffer size: " << width << ", " << height << std::endl;
}

// TODO: temp function, will be moved to Input
void Application::scrollCallback(double xoffset, double yoffset) {
    std::cout << "Scroll callback: " << xoffset << ", " << yoffset << std::endl;
}

// TODO: temp function, will be moved to Input
void Application::processInput() {
    GLFWwindow* window = this->window->getGLFWwindow();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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
