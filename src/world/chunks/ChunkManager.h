//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>
#include <glm/vec3.hpp>

#include "Chunk.h"
#include "../../graphics/BlockTextureAtlas.h"

const int START_CHUNKS_RADIUS = 5; // Number of chunks generated around spawn point at the start of the game.

class ChunkManager {
public:
    ChunkManager();

    void generateChunks();

    //TODO void loadChunk(glm::ivec2 pos); // Load chunk when perlin noise added
    Chunk& getChunk(glm::ivec2 pos);
    bool chunkExists(glm::ivec2 pos);
    Chunk& getChunk(glm::vec3 pos);
    bool chunkExists(glm::vec3 pos);


    std::map<std::pair<int, int>, Chunk>& getAllChunks();

private:
    std::map<std::pair<int, int>, Chunk> chunks;
    BlockTextureAtlas texAtlas;

    std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> generateChunkContent(glm::ivec2 pos);
};



#endif //CHUNKMANAGER_H
