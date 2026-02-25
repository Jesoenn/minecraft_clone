//
// Created by jakub on 16.02.2026.
//

#ifndef BLOCKTEXTUREATLAS_H
#define BLOCKTEXTUREATLAS_H
#include <map>
#include <memory>

#include "Texture.h"
#include "../core/World.h"
#include "../util/FaceDirection.h"

struct BlockTextures {
    Texture side_texture;
    Texture top_texture;
    Texture bottom_texture;
};

class BlockTextureAtlas {
public:
    const int blockTexSize = 16;

    BlockTextureAtlas(const char *path);

    // Getters
    glm::vec2 getAtlasSize();
    glm::vec2 getTextureCoords(BlockType blockType, FaceDirection faceDirection);

private:
    int atlasWidth, atlasHeight;
    std::unique_ptr<Texture> atlasTexture;

    // SetUp
    void loadAtlas(const char *path);
    void setUpBlockTextureOffsets();

    std::map<std::pair<BlockType, FaceDirection>, glm::vec2> texPos; // Bottom left of each texture
};



#endif //BLOCKTEXTUREATLAS_H
