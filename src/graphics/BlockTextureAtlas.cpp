//
// Created by jakub on 16.02.2026.
//

#include "BlockTextureAtlas.h"

#include <iostream>

BlockTextureAtlas::BlockTextureAtlas(const char *path):
    atlasWidth(-1), atlasHeight(-1) {
    loadAtlas(path);
    setUpBlockTextureOffsets();
}


void BlockTextureAtlas::setUpBlockTextureOffsets() {
    std::vector<FaceDirection> directions = {
        FaceDirection::FRONT, FaceDirection::BACK,
        FaceDirection::LEFT, FaceDirection::RIGHT,
        FaceDirection::TOP, FaceDirection::BOTTOM
    };

    glm::vec2 stonePos = glm::vec2(0.0f / atlasWidth, 0.0f / atlasHeight);
    glm::vec2 dirtPos = glm::vec2(16.0f / atlasWidth, 0.0f / atlasHeight);
    glm::vec2 grassBlockSide = glm::vec2(32.0f / atlasWidth, 0.0f / atlasHeight);
    glm::vec2 grassBlockTop = glm::vec2(48.0f / atlasWidth, 0.0f / atlasHeight);

    // STONE
    for (FaceDirection dir : directions) {
        texPos.emplace(std::make_pair(BlockType::STONE, dir),stonePos);
    }

    // DIRT
    for (FaceDirection dir: directions) {
        texPos.emplace(std::make_pair(BlockType::DIRT, dir),dirtPos);
    }

    // GRASS_BLOCK
    texPos.emplace(std::make_pair(BlockType::GRASS_BLOCK, FaceDirection::BOTTOM), dirtPos);
    texPos.emplace(std::make_pair(BlockType::GRASS_BLOCK, FaceDirection::TOP), grassBlockTop);
    for (FaceDirection dir : {FaceDirection::FRONT, FaceDirection::BACK, FaceDirection::LEFT, FaceDirection::RIGHT}) {
        texPos.emplace(std::make_pair(BlockType::GRASS_BLOCK, dir), grassBlockSide);
    }
}

glm::vec2 BlockTextureAtlas::getTextureCoords(BlockType blockType, FaceDirection faceDirection) {
    try {
        return texPos.at(std::make_pair(blockType, faceDirection));
    } catch (std::out_of_range& e) {
        std::cout<<"BLOCKTEXTUREATLAS::GETTEXTURECOORDS - No texture coordinates found for block type: " << static_cast<int>(blockType) << " and face direction: " << static_cast<int>(faceDirection) << std::endl;
        return {0.0f, 0.0f};
    }
}

void BlockTextureAtlas::loadAtlas(const char *path) {
    atlasTexture = std::make_unique<Texture>(path, TextureType::DIFFUSE);
    atlasWidth = atlasTexture->width;
    atlasHeight = atlasTexture->height;
}

/**
 * Returns atlas size in pixels.
 */
glm::vec2 BlockTextureAtlas::getAtlasSize() {
    return {atlasWidth, atlasHeight};
}

