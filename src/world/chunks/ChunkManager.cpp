//
// Created by jakub on 18.02.2026.
//

#include "ChunkManager.h"

#include <stdexcept>

ChunkManager::ChunkManager() {
    //TODO tmp - create function that created few chunks around the spawnpoint and move it to function
    chunks.insert({0,0}, Chunk(0, 0));
}

Chunk & ChunkManager::getChunk(glm::ivec2 pos) {
    try {
        return chunks.at(pos);
    } catch (std::out_of_range& e) {
        throw std::out_of_range("CHUNKMANAGER::getChunk: Chunk doesn't exist");
    }
}

Chunk & ChunkManager::getChunk(glm::vec3 pos) {
    // World position divide by chunk size, then floor down and multiply by chunk size -> (5, -2.5) is chunk (0, -16)
    glm::ivec2 chunkPos = glm::ivec2(std::floor(pos.x/CHUNK_SIZE_X)*CHUNK_SIZE_X, std::floor(pos.z/CHUNK_SIZE_Z)*CHUNK_SIZE_Z);
    return getChunk(chunkPos);
}

std::map<glm::ivec2, Chunk> & ChunkManager::getAllChunks() {
    return chunks;
}
