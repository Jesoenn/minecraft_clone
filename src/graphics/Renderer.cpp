//
// Created by jakub on 15.02.2026.
//

#include <glad/glad.h>
#include "Renderer.h"

#include <iostream>
#include <GLFW/glfw3.h>

Renderer::Renderer(Camera& camera, World& world, glm::vec2 windowSize):
    wireFrameMode(false),
    camera(camera), world(world), windowSize(windowSize),
    cubeVAO(0), cubeVBO(0), cubeShader(nullptr) {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    setUpShaders();
    setUpTextures();
    setUpCube();
}

//TODO:
// Kolizje, skakanie pod przycisk
// CHUNKI


void Renderer::render() {
    glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set shader uniforms
    cubeShader->use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov), windowSize.x/windowSize.y, 0.1f, 1000.0f);
    cubeShader->setMat4("projection", projection);
    cubeShader->setMat4("view", camera.getViewMatrix());

    glm::mat4 model;
    std::vector<glm::vec3> cubes = world.getBlockPositions();
    for (int i=0; i<cubes.size(); i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubes[i]);
        cubeShader->setMat4("model", model);

        blockTextureAtlas.activateTexture(world.getBlockType(i), 0, 1, 2);
        cubeShader->setInt("side_texture", 0);
        cubeShader->setInt("top_texture", 1);
        cubeShader->setInt("bottom_texture", 2);

        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}

void Renderer::toggleWireframe() {
    if (!wireFrameMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireFrameMode = true;
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireFrameMode = false;
    }
}

void Renderer::setWindowSize(glm::vec2 windowSize) {
    this->windowSize = windowSize;
}

void Renderer::setUpShaders() {
    cubeShader = std::make_shared<Shader>("../src/graphics/shaders/cube.vert", "../src/graphics/shaders/cube.frag");
}

void Renderer::setUpTextures() {
    blockTextureAtlas.loadAllTextures();
}

void Renderer::setUpCube() {
    float cubeVertices[] = {
        // positions          // normals          // tex coords

        // BACK
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,

        // FRONT
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,

        // LEFT
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        // RIGHT
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

        // BOTTOM
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

        // TOP
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
    };

    unsigned int cubeIndices[] = {
       0, 2, 1, 3, 2, 0,            // BACK
       4, 5, 6, 6, 7, 4,            // FRONT
       9, 8, 10, 11, 10, 8,         // LEFT
       12, 13, 14, 14, 15, 12,      // RIGHT
       16, 17, 18, 18, 19, 16,      // BOTTOM
       21, 20, 22, 23, 22, 20       // TOP
    };

    // Create and bind buffers
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind VAO
    glBindVertexArray(0);
}
