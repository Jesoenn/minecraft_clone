//
// Created by jakub on 14.02.2026.
//

#include "Application.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "../graphics/Camera.h"

Application::Application(int width, int height, const std::string& title):
    deltaTime(0.0f), lastFrame(0.0f),
    windowTitle(title) {
    createWindow(width, height, title);

    // Game objects
    world = std::make_shared<World>();
    renderer = std::make_shared<Renderer>(world->getCamera(), *world, window->getSize());
    input = std::make_shared<InputManager>(*world, *window, *renderer);

    // Create instances:
    // inputmanager - window reference
    // renderer - world reference, camera reference
    // world - idk

}

void Application::run() {
    while (!window->shouldClose()) {
        calculateFPS();
        input->processInput(deltaTime);

        // Update game state
        // update();

        // Rendering
        renderer->render();

        glfwSwapBuffers(window->getGLFWwindow());
        glfwPollEvents();
    }
}

void Application::createWindow(int width, int height, const std::string& title) {
    window = std::make_shared<Window>(width, height, title);
    window->setUp();

    // Set static GLFW callbacks to class functions
    window->setMouseCallback([this](double xPos, double yPos) {
        this->mouseCallback(xPos, yPos);
    });
    window->setScrollCallback([this](double xOffset, double yOffset) {
        this->scrollCallback(xOffset, yOffset);
    });
    window->setFrameBufferSizeCallback([this](int width, int height) {
        this->framebufferSizeCallback(width, height);
    });

}

void Application::calculateFPS() {
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    int fps = static_cast<int>(1.0f / deltaTime);
    glfwSetWindowTitle(window->getGLFWwindow(), (windowTitle + " - FPS: " + std::to_string(fps)).c_str());
}

void Application::mouseCallback(double xpos, double ypos) {
    input->mouseCallback(xpos, ypos);
}

void Application::scrollCallback(double xOffset, double yOffset) {
    input->scrollCallback(xOffset, yOffset);
}

void Application::framebufferSizeCallback(int width, int height) {
    renderer->setWindowSize(glm::vec2(width, height));
}
