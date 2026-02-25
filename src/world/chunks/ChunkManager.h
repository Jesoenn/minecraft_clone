//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>
#include <glm/vec3.hpp>

#include "Chunk.h"
#include "../../graphics/BlockTextureAtlas.h"


class ChunkManager {
public:
    ChunkManager();

    void generateChunks();

    //TODO void loadChunk(glm::ivec2 pos); // Load chunk when perlin noise added
    Chunk& getChunk(glm::ivec2 pos);
    Chunk& getChunk(glm::vec3 pos);
    std::map<std::pair<int, int>, Chunk>& getAllChunks();

private:
    std::map<std::pair<int, int>, Chunk> chunks;

    BlockTextureAtlas texAtlas;
};



#endif //CHUNKMANAGER_H
