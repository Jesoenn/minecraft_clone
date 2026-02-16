//
// Created by jakub on 14.02.2026.
//
#include <glad/glad.h>
#include "Window.h"
#include <iostream>


Window::Window(int width, int height, std::string title):
    width(width), height(height), title(title),
    window(nullptr){

    // Set initial mouse position to center of the window
    lastMouseX = static_cast<float>(width)/2.0f;
    lastMouseY = static_cast<float>(height)/2.0f;
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

/**
 * Initialize GLFW, create window, set up OpenGL context, callbacks for window resizing, scroll and mouse input.
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

    setCallbacks();
}

void Window::setCallbacks() {
    // Add new pointer to current class instance, so it can be referenced in static callback functions
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void Window::setMouseCallback(std::function<void(double, double)> func) {
    this->mouseCallbackFunc = std::move(func);
}

void Window::setScrollCallback(std::function<void(double, double)> func) {
    this->scrollCallbackFunc = std::move(func);
}

void Window::setFrameBufferSizeCallback(std::function<void(int, int)> func) {
    this->frameBufferSizeCallbackFunc = std::move(func);
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
    return {static_cast<float>(width), static_cast<float>(height)};
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

//
// Static callback functions defined by GLFW.
//

void Window::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->mouseCallbackFunc(xpos, ypos);
}

void Window::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->width = width;
    win->height = height;

    win->frameBufferSizeCallbackFunc(width, height);
}

void Window::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->scrollCallbackFunc(xoffset, yoffset);
}