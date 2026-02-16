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

void World::processMovement(CameraMovement direction, float deltaTime) {
    //TODO: CHECK COLLISIONS BY CHUNK

    if (!physicsEnabled) {
        camera.processInput(direction, deltaTime);

        float hitBoxY = camera.position.y - (player.getEyeHeight() - player.getHeight() / 2.0f);
        player.setPosition(camera.position.x, hitBoxY, camera.position.z);
        return;
    }

    // Movement direction vector
    glm::vec3 moveDir(0.0f);
    switch (direction) {
        case FORWARD: moveDir = camera.front; break;
        case BACKWARD: moveDir = -camera.front; break;
        case LEFT: moveDir = -camera.right; break;
        case RIGHT: moveDir = camera.right; break;
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



bool World::checkCollision(const glm::vec3 newPos) {
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
