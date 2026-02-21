//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>
#include <glm/vec3.hpp>

#include "Chunk.h"


class ChunkManager {
    ChunkManager();
    //TODO void loadChunk(glm::ivec2 pos); // Load chunk when perlin noise added
    Chunk& getChunk(glm::ivec2 pos);
    Chunk& getChunk(glm::vec3 pos);
    std::map<glm::ivec2, Chunk>& getAllChunks();

private:
    std::map<glm::ivec2, Chunk> chunks;

};



#endif //CHUNKMANAGER_H
