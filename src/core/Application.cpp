//
// Created by jakub on 14.02.2026.
//

#include "Application.h"
#include "GLFW/glfw3.h"
#include <iostream>

Application::Application(int width, int height, const std::string& title):
    windowTitle(title), deltaTime(0.0f), lastFrame(0.0f) {
    createWindow(width, height, title);
}

void Application::run() {
    while (!window->shouldClose()) {
        calculateFPS();

        // Keyboard input processing
        // input.process(window);

        // Update game state
        // update();

        // Rendering
        // render();
    }
}

void Application::createWindow(int width, int height, const std::string& title) {
    // TODO: FINISH BELOW
    // Create window
    // Add app to window
    // Whenever callback happens, application processes it. But how?

    window = std::make_shared<Window>(width, height, title);
    window->setUp();

}

void Application::calculateFPS() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    int fps = static_cast<int>(1.0f / deltaTime);
    glfwSetWindowTitle(window->getGLFWwindow(), (windowTitle + " - FPS: " + std::to_string(fps)).c_str());
}

void Application::mouseCallback(double xpos, double ypos) {
    throw std::runtime_error("Mouse callback not implemented yet");
}

void Application::frameBufferSizeCallback(int width, int height) {
    throw std::runtime_error("Frame buffer size callback not implemented yet");
}

void Application::scrollCallback(double xoffset, double yoffset) {
    throw std::runtime_error("Scroll callback not implemented yet");
}
