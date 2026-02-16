//
// Created by jakub on 16.02.2026.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr glm::vec3 DEFAULT_UP = glm::vec3(0.f, 1.f, 0.f);
constexpr glm::vec3 DEFAULT_RIGHT = glm::vec3(1.f, 0.f, 0.f);
constexpr glm::vec3 DEFAULT_FRONT = glm::vec3(0.f, 0.f, -1.f);
constexpr glm::vec3 DEFAULT_POS = glm::vec3(0.f, 0.f, 0.f);
constexpr glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.f, 1.f, 0.f);
constexpr float DEFAULT_FOV = 45.f;
constexpr float DEFAULT_PITCH = 0.f;
constexpr float DEFAULT_YAW = -90.f;
constexpr float DEFAULT_MOVEMENT_SPEED = 10.0f;
constexpr float DEFAULT_MOUSE_SENSITIVITY = 0.1f;

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
    // Camera vectors
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Camera attributes in degrees
    float yaw, pitch;   // left/right, up/down rotation
    float fov;          // low = zoom in, high = zoom out

    // Moving attributes
    float movementSpeed, mouseSensitivity;

    Camera();
    explicit Camera(glm::vec3 pos);
    void processInput(CameraMovement direction, float deltaTime);
    void processScroll(double yOffset);
    void processMouseMovement(float xOffset, float yOffset);

    glm::mat4 getViewMatrix() const;

private:
    void updateCameraVectors();

};


#endif //CAMERA_H
