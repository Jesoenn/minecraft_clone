//
// Created by jakub on 16.02.2026.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <glm/vec3.hpp>

#define PLAYER_WIDTH 0.6f;
#define PLAYER_HEIGHT 1.8125f;
#define PLAYER_DEPTH 0.6f;
#define EYE_HEIGHT 1.62f;

class Player {
public:
    explicit Player(float cameraY);

    void setUpHitBox(float cameraY);
    // Setters
    void setPosition(const glm::vec3& newPosition);
    void setPosition(float x, float y, float z);

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getSize() const;
    float getWidth() const;
    float getHeight() const;
    float getDepth() const;
    float getEyeHeight() const;

private:
    glm::vec3 position;
    float width, height, depth, eyeHeight;

};

#endif //PLAYER_H
