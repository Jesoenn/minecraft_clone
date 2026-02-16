//
// Created by jakub on 16.02.2026.
//

#include "Camera.h"

Camera::Camera():
    position(DEFAULT_POS), front(DEFAULT_POS), up(DEFAULT_UP), right(DEFAULT_RIGHT), worldUp(DEFAULT_WORLD_UP),
    yaw(DEFAULT_YAW), pitch(DEFAULT_PITCH), fov(DEFAULT_FOV), movementSpeed(DEFAULT_MOVEMENT_SPEED), mouseSensitivity(DEFAULT_MOUSE_SENSITIVITY){}

Camera::Camera(glm::vec3 pos):
    position(pos), front(DEFAULT_POS), up(DEFAULT_UP), right(DEFAULT_RIGHT), worldUp(DEFAULT_WORLD_UP),
    yaw(DEFAULT_YAW), pitch(DEFAULT_PITCH), fov(DEFAULT_FOV), movementSpeed(DEFAULT_MOVEMENT_SPEED), mouseSensitivity(DEFAULT_MOUSE_SENSITIVITY){}

void Camera::processInput(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    switch (direction) {
        case FORWARD: position += velocity * front; break;
        case BACKWARD: position -= velocity * front; break;
        case LEFT: position -= velocity * right; break;
        case RIGHT: position += velocity * right; break;
    }
}

void Camera::processScroll(double yOffset) {
    fov -= static_cast<float>(yOffset);
    if (fov < 1.0f)
        fov = 1.0f;
    else if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
    // Calculate new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);

    // Calculate new right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
