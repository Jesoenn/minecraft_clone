//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>
#include <glm/vec3.hpp>

#include "Chunk.h"


class ChunkManager {

    //TODO void loadChunk(glm::vec3 pos); // Load chunk when perlin noise added
    Chunk& getChunk(glm::ivec3 pos);

private:
    std::map<glm::ivec3, Chunk> chunks;


};



#endif //CHUNKMANAGER_H
