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
    void setUp();

    // Setters
    void setTitle(std::string title);
    void setSize(int width, int height);

    // Getters
    GLFWwindow* getGLFWwindow();
    glm::vec2 getSize();
    bool shouldClose();

private:
    int width, height;
    std::string title;
    GLFWwindow* window; // Pointer to GLFW window, so that we can call glfw functions on it

    void setCallbacks();

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    // void static processInput(GLFWwindow* window);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};



#endif //WINDOW_H
