//
// Created by jakub on 14.02.2026.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <memory>
#include <string>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>


class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();
    void setUp();

    // Setters
    void setTitle(std::string title);
    void setSize(int width, int height);
    void setMouseCallback(std::function<void(double, double)> func);
    void setFrameBufferSizeCallback(std::function<void(int, int)> func);
    void setScrollCallback(std::function<void(double, double)> func);

    // Getters
    GLFWwindow* getGLFWwindow();
    glm::vec2 getSize();
    bool shouldClose();

private:
    int width, height;
    float lastMouseX, lastMouseY;
    std::string title;
    GLFWwindow* window; // GLFW window

    // Implemented callback functions. They have to be set by parent class.
    void setCallbacks();
    std::function<void(double, double)> mouseCallbackFunc;
    std::function<void(int, int)> frameBufferSizeCallbackFunc;
    std::function<void(double, double)> scrollCallbackFunc;

    // Static callbacks defined by GLFW. They call corresponding std::function callbacks.
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};



#endif //WINDOW_H
