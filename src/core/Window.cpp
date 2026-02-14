//
// Created by jakub on 14.02.2026.
//
#include <glad/glad.h>
#include "Window.h"
#include <iostream>


Window::Window(int width, int height, std::string title):
    width(width), height(height), title(title),
    window(nullptr) {}

/**
 * Initializes GLFW, creates a window, and sets up OpenGL context.
 * Also sets up callbacks for window resizing, scroll and mouse input.
 */
void Window::setUp() {
    // Initialize GLFW and set OpenGL version to 3.3 core profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Major OpenGL Version -> 3.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // Minor OpenGL Version -> .3 (3.3)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if ( window == NULL ) {
        std::cout << "Failed to create GLFW window. Exiting..." << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Disable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // Set viewport and lock cursor to window
    glViewport(0, 0, width, height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock cursor to window

    // Set up callbacks for window resizing, scroll and mouse input
    setCallbacks();
}

void Window::setCallbacks() {
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback); // Changing window size
    glfwSetCursorPosCallback(window, mouseCallback); // Moving/Pressing mouse
    glfwSetScrollCallback(window, scrollCallback);  // Scroll callback
}

void Window::mouseCallback(GLFWwindow *window, double xpos, double ypos) {

}

void Window::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {

}

void Window::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

}

void Window::setTitle(std::string title) {
    this->title = std::move(title);
    glfwSetWindowTitle(window, this->title.c_str());
}

void Window::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    glfwSetWindowSize(window, width, height);
}

GLFWwindow* Window::getGLFWwindow() {
    return window;
}

glm::vec2 Window::getSize() {
    return {width, height};
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}
