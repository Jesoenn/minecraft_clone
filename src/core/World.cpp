//
// Created by jakub on 16.02.2026.
//

#include "World.h"

#include <iostream>

World::World() {
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
            blockPositions.emplace_back(i, -1.f, j);
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
}

void World::processMovement(CameraMovement direction, float deltaTime) {
    camera.processInput(direction, deltaTime);
}

void World::processMouseMovement(float xOffset, float yOffset) {
    camera.processMouseMovement(xOffset, yOffset);
}

void World::processScroll(double yOffset) {
    camera.processScroll(yOffset);
}

Camera & World::getCamera() {
    return camera;
}

std::vector<glm::vec3> World::getBlockPositions() const {
    return blockPositions;
}

BlockType World::getBlockType(int blockId) const {
    return blocks[blockId].getType();
}

std::vector<Block> World::getBlocks() const {
    return blocks;
}
