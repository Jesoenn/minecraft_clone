//
// Created by jakub on 15.02.2026.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <memory>
#include <vector>
#include <GL/gl.h>
#include "Camera.h"
#include "Shader.h"


class Renderer {
public:
    Renderer(Camera& camera);

    void render();

    // TODO: tmp, move to chunks
    void setUpShaders();
    void setUpCubes();
    void setUpCubeCoords();

private:
    Camera camera;

    // TODO: tmp
    std::vector<glm::vec3> cubeCoords;
    GLuint cubeVAO, cubeVBO;
    std::shared_ptr<Shader> cubeShader;

};



#endif //RENDERER_H
