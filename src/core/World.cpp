//
// Created by jakub on 16.02.2026.
//

#include "World.h"

#include <iostream>

World::World(): player(0.0f), physicsEnabled(false) {
    setUp();
}

void World::setUp() {
    // 16x16x256 - 14fps

    for (int i =0; i<16; i++) {
        for (int j=0; j<16; j++) {
            // for (int k=0; k<256; k++) {
            //     blockPositions.emplace_back(i, -k, j);
            //     blocks.emplace_back(BlockType::GRASS_BLOCK);
            // }
            blockPositions.emplace_back(i+1, -1.f, j);
            if (j%2 == 0) {
                blocks.emplace_back(BlockType::GRASS_BLOCK);
            } else {
                blocks.emplace_back(BlockType::DIRT);
            }
        }
    }
    // 1 block above plane
    blockPositions.emplace_back(6.f, 0.f, 6.f);
    blocks.emplace_back(BlockType::GRASS_BLOCK);
    // Ceiling
    blockPositions.emplace_back(10.f, 2.f, 4.f);
    blocks.emplace_back(BlockType::DIRT);

    blockPositions.emplace_back(0.f, 1.f, -2.f);
    blocks.emplace_back(BlockType::GRASS_BLOCK);

    blockPositions.emplace_back(3.f, 1.f, -2.f);
    blocks.emplace_back(BlockType::DIRT);

    // box
    blockPositions.emplace_back(-3.f, 0.f, -2.f);
    blocks.emplace_back(BlockType::DIRT);
    blockPositions.emplace_back(-4.f, 0.f, -1.f);
    blocks.emplace_back(BlockType::DIRT);
}

void World::updatePhysics(const float deltaTime) {
    if (!physicsEnabled) {
        return;
    }

    jumpPhysics(deltaTime);
}

void World::processMovement(CameraMovement direction, float deltaTime) {
    //TODO: CHECK COLLISIONS BY CHUNK
    if (!physicsEnabled) {
        camera.processInput(direction, deltaTime);

        float hitBoxY = camera.position.y - (player.getEyeHeight() - player.getHeight() / 2.0f);
        player.setPosition(camera.position.x, hitBoxY, camera.position.z);
        return;
    }

    // Movement direction vector
    glm::vec3 moveDir = -glm::normalize(glm::cross(camera.right, camera.worldUp)); // Front without Y axis
    switch (direction) {
        case FORWARD: break;
        case BACKWARD: moveDir *= -1; break;
        case LEFT: moveDir = -camera.right; break;
        case RIGHT: moveDir = camera.right; break;
        case JUMP:
            if (player.isOnGround()) {
                player.setVelocity(glm::vec3(0.0f, JUMP_FORCE, 0.0f));
            }
            return;
    }

    float velocity = camera.movementSpeed * deltaTime;
    glm::vec3 currentPos = player.getPosition();

    // Check each axis to allow movement on non-colliding axes (allows sliding along walls)
    // X axis
    glm::vec3 newPosX = currentPos;
    newPosX.x += moveDir.x * velocity;
    if (!checkCollision(newPosX)) {
        currentPos.x = newPosX.x;
    }
    // Z axis
    glm::vec3 newPosZ = currentPos;
    newPosZ.z += moveDir.z * velocity;
    if (!checkCollision(newPosZ)) {
        currentPos.z = newPosZ.z;
    }
    // Y axis
    glm::vec3 newPosY = currentPos;
    newPosY.y += moveDir.y * velocity;
    if (!checkCollision(newPosY)) {
        currentPos.y = newPosY.y;
    }

    // Set positions
    player.setPosition(currentPos.x, currentPos.y, currentPos.z);
    camera.position.x = currentPos.x;
    camera.position.z = currentPos.z;
    camera.position.y = currentPos.y + player.getEyeHeight() - player.getHeight() / 2.0f;
}

void World::jumpPhysics(float deltaTime) {
    glm::vec3 velocity = player.getVelocity();

    // If player is not jumping - check if walked of a block
    if (player.isOnGround() && velocity.y == 0.0f)
        calcPlayerOnGround();

    // Check if player just jumped
    if (velocity.y != 0.0f && player.isOnGround()) {
        player.setOnGround(false);
    }
    // If not jumping or falling
    else if (velocity.y == 0.0f && player.isOnGround()) {
        return;
    }

    // Apply gravity
    velocity.y -= GRAVITY * deltaTime;
    // Limit max falling speed
    if (velocity.y < -MAX_Y_VELOCITY) {
        velocity.y = -MAX_Y_VELOCITY;
    }

    glm::vec3 newPos = player.getPosition() + velocity * deltaTime;
    if (checkCollision(newPos)) {
        // If player was falling (collision from below), he is on the ground
        if (velocity.y < 0 ) {
            player.setOnGround(true);
        }
        velocity.y = 0;
    } else {
        player.setPosition(newPos.x, newPos.y, newPos.z);
        camera.position.x = newPos.x;
        camera.position.z = newPos.z;
        camera.position.y = newPos.y + player.getEyeHeight() - player.getHeight() / 2.0f;
    }
    // calcPlayerOnGround();
    player.setVelocity(velocity);
}


bool World::checkCollision(const glm::vec3 newPos) {
    // TODO check by chunk and in radius - for example 3
    for (glm::vec3 &block : blockPositions) {
        float distance = glm::length(block - player.getPosition());
        if (distance > 3.8f) {
            continue;
        }
        glm::vec3 playerSize = player.getSize();

        // AABB collision check
        // https://www.youtube.com/watch?v=59BTXB-kFNs
        if ( newPos.x - playerSize.x/2 < block.x + 0.5f && newPos.x + playerSize.x/2 > block.x - 0.5f &&
             newPos.y - playerSize.y/2 < block.y + 0.5f && newPos.y + playerSize.y/2 > block.y - 0.5f &&
             newPos.z - playerSize.z/2 < block.z + 0.5 && newPos.z + playerSize.z/2 > block.z - 0.5f) {

            return true;
        }
    }
    return false;
}

void World::calcPlayerOnGround() {
    glm::vec3 newPos = player.getPosition();
    newPos.y -=  0.01f; // Check slightly below the player
    if (!checkCollision(newPos)) {
        player.setOnGround(false);
    } else {
        player.setOnGround(true);
    }
}

void World::processMouseMovement(const float xOffset, const float yOffset) {
    camera.processMouseMovement(xOffset, yOffset);
}

void World::processScroll(const double yOffset) {
    camera.processScroll(yOffset);
}

void World::togglePhysics() {
    physicsEnabled = !physicsEnabled;
    if (physicsEnabled) {
        std::cout << "Physics enabled" << std::endl;
    } else {
        player.setVelocity(glm::vec3(0));
        std::cout << "Physics disabled" << std::endl;
    }
}

Camera & World::getCamera() {
    return camera;
}

std::vector<glm::vec3> World::getBlockPositions() const {
    return blockPositions;
}

BlockType World::getBlockType(const int blockId) const {
    return blocks[blockId].getType();
}

std::vector<Block> World::getBlocks() const {
    return blocks;
}
