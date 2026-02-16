//
// Created by jakub on 15.02.2026.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <memory>
#include <vector>
#include <GL/gl.h>

#include "BlockTextureAtlas.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "../core/World.h"


class Renderer {
public:
    Renderer(Camera& camera, World& world, glm::vec2 windowSize);

    void render();
    void toggleWireframe();

    // Set up
    void setUpShaders();
    void setUpTextures();
    void setUpCube();

    // Setters
    void setWindowSize(glm::vec2 windowSize);

private:
    bool wireFrameMode;

    Camera& camera;
    World& world;
    BlockTextureAtlas blockTextureAtlas;

    glm::vec2 windowSize;

    // Visual
    GLuint cubeVAO, cubeVBO, cubeEBO;
    std::shared_ptr<Shader> cubeShader;
};



#endif //RENDERER_H
