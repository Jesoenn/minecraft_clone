//
// Created by jakub on 18.02.2026.
//

#include "ChunkManager.h"

#include <stdexcept>

ChunkManager::ChunkManager():
    texAtlas("../resources/texture_atlas.png") {
    generateChunks();
}

/* Generate chunks around spawn point in given START_CHUNK radius */
void ChunkManager::generateChunks() {
    for (int x = -START_CHUNKS_RADIUS; x <= START_CHUNKS_RADIUS; x++) {
        for (int z = -START_CHUNKS_RADIUS; z <= START_CHUNKS_RADIUS; z++) {
            glm::ivec2 chunkPos = {x*CHUNK_SIZE_X, z*CHUNK_SIZE_Z};
            chunks.insert({{chunkPos.x, chunkPos.y}, Chunk(chunkPos.x, chunkPos.y, texAtlas, generateChunkContent(chunkPos))});
        }
    }
}

std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> ChunkManager::generateChunkContent(glm::ivec2 pos) {
    std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks = {};

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                if (y < 6) {
                    blocks[x][y][z] = BlockType::DIRT;
                } else if (y == 6 || y == 7) {
                    blocks[x][y][z] = BlockType::AIR;
                } else if (y < 11) {
                    blocks[x][y][z] = BlockType::STONE;
                } else if (y == 11 || y == 12) {
                    blocks[x][y][z] = BlockType::AIR;
                } else {
                    blocks[x][y][z] = BlockType::GRASS_BLOCK;
                }
            }
        }
    }

    blocks[5][13][5] = BlockType::AIR;
    blocks[5][14][5] = BlockType::AIR;
    blocks[5][15][5] = BlockType::AIR;
    blocks[5][13][4] = BlockType::AIR;
    blocks[5][14][4] = BlockType::AIR;
    blocks[5][15][4] = BlockType::AIR;
    blocks[4][13][5] = BlockType::AIR;
    blocks[4][14][5] = BlockType::AIR;
    blocks[4][15][5] = BlockType::AIR;
    blocks[4][13][4] = BlockType::AIR;
    blocks[4][14][4] = BlockType::AIR;
    blocks[4][15][4] = BlockType::AIR;

    return blocks;
}


Chunk & ChunkManager::getChunk(glm::ivec2 pos) {
    try {
        return chunks.at(std::make_pair(pos.x, pos.y));
    } catch (std::out_of_range& e) {
        throw std::out_of_range("CHUNKMANAGER::getChunk: Chunk doesn't exist");
    }
}

Chunk & ChunkManager::getChunk(glm::vec3 pos) {
    // World position divide by chunk size, then floor down and multiply by chunk size -> (5, -2.5) is chunk (0, -16)
    glm::ivec2 chunkPos = glm::ivec2(std::floor(pos.x/CHUNK_SIZE_X)*CHUNK_SIZE_X, std::floor(pos.z/CHUNK_SIZE_Z)*CHUNK_SIZE_Z);
    return getChunk(chunkPos);
}

std::map<std::pair<int, int>, Chunk> & ChunkManager::getAllChunks() {
    return chunks;
}

