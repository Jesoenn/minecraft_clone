//
// Created by jakub on 16.02.2026.
//

#include "BlockTextureAtlas.h"

#include <iostream>

BlockTextureAtlas::BlockTextureAtlas() {

}

void BlockTextureAtlas::loadAllTextures() {
    Texture dirtTexture = loadTexture("../resources/dirt.png");
    textureMap.emplace(BlockType::DIRT, BlockTextures(
        dirtTexture,
        dirtTexture,
        dirtTexture
    ));
    textureMap.emplace(BlockType::GRASS_BLOCK, BlockTextures(
        loadTexture("../resources/grass_block_side.png"),
        loadTexture("../resources/grass_block_top.png"),
        dirtTexture
    ));


}

Texture BlockTextureAtlas::loadTexture(const char *path) {
    return Texture(path, TextureType::DIFFUSE);
}


void BlockTextureAtlas::activateTexture(BlockType blockType, int sideTextureUnit, int topTextureUnit, int bottomTextureUnit) {
    auto it = textureMap.find(blockType);
    if (it != textureMap.end()) {
        it->second.side_texture.bind(sideTextureUnit);
        it->second.top_texture.bind(topTextureUnit);
        it->second.bottom_texture.bind(bottomTextureUnit);
    } else {
        std::cout<<"No textures found for block type: " << static_cast<int>(blockType) << std::endl;
    }
}

