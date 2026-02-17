//
// Created by jakub on 16.02.2026.
//

#include "Player.h"

Player::Player(float cameraY):
    position(glm::vec3(0)), velocity(glm::vec3(0)), onGround(false),
    width(0), height(0), depth(0), eyeHeight(0) {
    setUpHitBox(cameraY);
}

void Player::setUpHitBox(float cameraY) {
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;
    depth = PLAYER_DEPTH;
    eyeHeight = EYE_HEIGHT;

    // Calc hitBox position based on eye height
    position = glm::vec3(0, cameraY - eyeHeight + height/2, 0);
}

void Player::setPosition(const glm::vec3 &newPosition) {
    position = newPosition;
}

void Player::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

void Player::setVelocity(const glm::vec3 &newVelocity) {
    velocity = newVelocity;
}

void Player::setVelocity(float x, float y, float z) {
    velocity = glm::vec3(x, y, z);
}

void Player::setOnGround(bool onGround) {
    this->onGround = onGround;
}

glm::vec3 Player::getVelocity() const {
    return velocity;
}


glm::vec3 Player::getPosition() const {
    return position;
}

glm::vec3 Player::getSize() const {
    return glm::vec3(width, height, depth);
}

float Player::getWidth() const {
    return width;
}

float Player::getHeight() const {
    return height;
}

float Player::getDepth() const {
    return depth;
}

float Player::getEyeHeight() const {
    return eyeHeight;
}

bool Player::isOnGround() const {
    return onGround;
}
