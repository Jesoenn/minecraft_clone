//
// Created by jakub on 16.02.2026.
//

#ifndef BLOCKTEXTUREATLAS_H
#define BLOCKTEXTUREATLAS_H
#include <map>

#include "Texture.h"
#include "../core/World.h"

struct BlockTextures {
    Texture side_texture;
    Texture top_texture;
    Texture bottom_texture;
};

class BlockTextureAtlas {
public:
    BlockTextureAtlas();

    void loadAllTextures();
    Texture loadTexture(const char *path);

    void activateTexture(BlockType blockType, int textureUnit, int topTextureUnit, int bottomTextureUnit);
private:
    std::map<BlockType, BlockTextures> textureMap;

};



#endif //BLOCKTEXTUREATLAS_H
