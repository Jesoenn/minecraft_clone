//
// Created by jakub on 16.02.2026.
//

#include "World.h"

#include <iostream>
#include <GLFW/glfw3.h>

World::World(ChunkManager& chunkManager): player(0.0f), chunkManager(chunkManager), physicsEnabled(false) {
    setUp();
}

void World::setUp() {
    //Set player location
    if (!chunkManager.chunkExists(player.getPosition())) {
        std::cout<<"WORLD::SETUP: Player spawn point is in non existing chunk\n";
        return;
    }
    auto& blocks = chunkManager.getChunk(player.getPosition()).getBlocks();
    for (int y = CHUNK_SIZE_Y-1; y >=0; y--) {
        if (blocks[0][y][0] != BlockType::AIR) {
            // Increase player y position from 0 to above ground
            glm::vec3 yBoost = glm::vec3(0.0f, y+3, 0.0f);
            player.setPosition(player.getPosition()+yBoost);
            camera.position += yBoost;
            return;
        }
    }
}

void World::updatePhysics(const float deltaTime) {
    if (!physicsEnabled) {
        return;
    }
    jumpPhysics(deltaTime);
}

void World::processMovement(CameraMovement direction, float deltaTime) {
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

void World::destroyBlock() {
    glm::vec3 rayOrigin = camera.position;
    glm::vec3 rayDir = camera.front;
    float maxDist = 4.5f;
    float step = 0.1f;

    for (float dist = 0.f; dist < maxDist; dist += step) {
        glm::vec3 pos = rayOrigin + rayDir * dist;
        glm::ivec3 blockPos = glm::round(pos);

        if (!chunkManager.isGlobalBlockAir(blockPos.x, blockPos.y, blockPos.z)) {
            chunkManager.setGlobalBlock(glm::ivec3(blockPos), BlockType::AIR);
            break;
        }
    }
}

void World::placeBlock() {
    glm::vec3 rayOrigin = camera.position;
    glm::vec3 rayDir = camera.front;
    float maxDist = 5.f;
    float step = 0.1f;

    glm::ivec3 lastAirBlock(0, -1, 0); // Initialize with invalid position
    for (float dist = 0.f; dist < maxDist; dist += step) {
        glm::vec3 pos = rayOrigin + rayDir * dist;
        glm::ivec3 blockPos = glm::round(pos);

        if (chunkManager.isGlobalBlockAir(blockPos.x, blockPos.y, blockPos.z)) {
            lastAirBlock = blockPos;
        } else {

            if (lastAirBlock.y != -1) {
                glm::vec3 playerPos = player.getPosition();
                glm::ivec3 playerBlockPos = glm::ivec3(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y), static_cast<int>(playerPos.z));

                if (playerBlockPos == lastAirBlock || playerBlockPos + glm::ivec3(0,1,0) == lastAirBlock) {
                    return;
                }

                chunkManager.setGlobalBlock(lastAirBlock, player.getBlockInHand());
            }
            break;
        }
    }
}

void World::cycleBlockInHand() {
    BlockType blockType = player.getBlockInHand();
    int blockTypeInt = static_cast<int>(blockType);
    if (blockType == BlockType::STONE) {
        blockTypeInt = 0;
    } else {
        blockTypeInt++;
    }

    player.setBlockInHand(static_cast<BlockType>(blockTypeInt));
    player.printBlockInHand();
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
    glm::vec3 collision_radius = glm::vec3(2);
    glm::vec3 playerPos = player.getPosition();
    glm::ivec3 minBlock = glm::floor(playerPos - collision_radius);
    glm::ivec3 maxBlock = glm::floor(playerPos + collision_radius);

    for (int x = minBlock.x; x <= maxBlock.x; x++) {
        for (int z = minBlock.z; z <= maxBlock.z; z++) {
            // Get chunk based on x and z
            glm::vec3 blockPos(x, 0, z);
            if (!chunkManager.chunkExists(blockPos))
                continue;
            Chunk& chunk = chunkManager.getChunk(blockPos);

            for (int y = minBlock.y; y <= maxBlock.y; y++) {
                blockPos.y = y;

                // Position in chunk
                glm::ivec3 localPos = glm::ivec3(x-chunk.getPosition().x, y, z-chunk.getPosition().y);
                if ( localPos.y < 0 || localPos.y >= CHUNK_SIZE_Y )
                    continue;

                auto& blocks = chunk.getBlocks();
                if (blocks[localPos.x][localPos.y][localPos.z] == BlockType::AIR)
                    continue;

                glm::vec3 playerSize = player.getSize();
                // AABB collision check
                // https://www.youtube.com/watch?v=59BTXB-kFNs
                if ( newPos.x - playerSize.x/2 < blockPos.x + 0.5f && newPos.x + playerSize.x/2 > blockPos.x - 0.5f &&
                     newPos.y - playerSize.y/2 < blockPos.y + 0.5f && newPos.y + playerSize.y/2 > blockPos.y - 0.5f &&
                     newPos.z - playerSize.z/2 < blockPos.z + 0.5f && newPos.z + playerSize.z/2 > blockPos.z - 0.5f) {
                    return true;
                }

            }
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
        camera.setWalkingSpeed();
        std::cout << "Physics enabled" << std::endl;
    } else {
        player.setVelocity(glm::vec3(0));
        camera.setFlyingSpeed();
        std::cout << "Physics disabled" << std::endl;
    }
}

Camera & World::getCamera() {
    return camera;
}

glm::vec3 World::getGlobalLightColor() const {
    return globalLight.color;
}

glm::vec3 World::getGlobalLightDir() const {
    return globalLight.dir;
}
