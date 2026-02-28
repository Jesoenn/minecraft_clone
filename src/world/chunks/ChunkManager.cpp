//
// Created by jakub on 18.02.2026.
//

#include "ChunkManager.h"

#include <iostream>
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
            chunks.insert({{chunkPos.x, chunkPos.y}, Chunk(chunkPos.x, chunkPos.y, texAtlas, generateChunkContent(chunkPos), [this](int x, int y, int z) { return isGlobalBlockAir(x, y, z); })});
        }
    }

    for (auto& [pos, chunk] : chunks) {
        chunk.buildMesh();
    }
}

std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> ChunkManager::generateChunkContent(glm::ivec2 pos) {
    std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks = {};

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            glm::vec2 tmp = glm::vec2(x+pos.x, z+pos.y);

            int maxY = 6+3*(std::sin(1.f/5.f*tmp.x)+std::cos(1.f/5.f*tmp.y));

            blocks[x][maxY][z] = BlockType::GRASS_BLOCK;

            for (int y = 0; y < maxY-1; y++) {
                blocks[x][y][z] = BlockType::STONE;
            }
            if (maxY-1 >= 0)
                blocks[x][maxY-1][z] = BlockType::DIRT;
        }
    }

    return blocks;


    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                if (y < 6) {
                    blocks[x][y][z] = BlockType::DIRT;
                } else if (y == 6 || y == 7) {
                    blocks[x][y][z] = BlockType::AIR;
                } else if (y < 11) {
                    blocks[x][y][z] = BlockType::STONE;
                } else if (y == 11 || y == 12 || y==15) {
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

    for (int z = 0; z < CHUNK_SIZE_Z; z++) {
        if (z%2 == 0)
            blocks[0][15][z] = BlockType::STONE;
    }

    return blocks;
}


Chunk & ChunkManager::getChunk(glm::ivec2 pos) {
    try {
        return chunks.at(std::make_pair(pos.x, pos.y));
    } catch (std::out_of_range& e) {
        throw std::out_of_range("CHUNKMANAGER::getChunk: Chunk doesn't exist");
    }
}

bool ChunkManager::chunkExists(glm::ivec2 pos) {
    try {
        getChunk(pos);
    } catch (std::out_of_range& e) {
        return false;
    }
    return true;
}

Chunk & ChunkManager::getChunk(glm::vec3 pos) {
    // World position divide by chunk size, then floor down and multiply by chunk size -> (5, -2.5) is chunk (0, -16)
    glm::ivec2 chunkPos = glm::ivec2(std::floor(pos.x/CHUNK_SIZE_X)*CHUNK_SIZE_X, std::floor(pos.z/CHUNK_SIZE_Z)*CHUNK_SIZE_Z);
    return getChunk(chunkPos);
}

bool ChunkManager::chunkExists(glm::vec3 pos) {
    try {
        getChunk(pos);
    } catch (std::out_of_range& e) {
        return false;
    }
    return true;
}

std::map<std::pair<int, int>, Chunk> & ChunkManager::getAllChunks() {
    return chunks;
}

bool ChunkManager::isGlobalBlockAir(int x, int y, int z) {
    glm::vec3 pos = glm::vec3(x, y, z);
    if (!chunkExists(pos))
        return true;

    Chunk& chunk = getChunk(pos);
    int localX = x - chunk.getPosition().x;
    int localZ = z - chunk.getPosition().y;
    auto blocks = chunk.getBlocks();

    if (y >= CHUNK_SIZE_Y || y < 0) {
        return true;
    }

    return blocks[localX][y][localZ] == BlockType::AIR;
}

void ChunkManager::setGlobalBlock(glm::ivec3 pos, BlockType block) {
    glm::vec3 fPos = pos;

    if (!chunkExists(fPos) || pos.y >= CHUNK_SIZE_Y || pos.y < 0)
        return;

    Chunk& chunk = getChunk(fPos);
    int localX = pos.x - chunk.getPosition().x;
    int localZ = pos.z - chunk.getPosition().y;

    chunk.setBlock(glm::ivec3(localX, pos.y, localZ), block);
    chunk.buildMesh();

    // Build mesh of neighboring chunks if block was destroyed on chunk edge
    if (localX == CHUNK_SIZE_X-1 || localX == 0) {
        glm::vec3 neighborPos = glm::vec3(fPos.x - ((localX == 0) ? 1.f : -1.f), fPos.y, fPos.z);
        if (chunkExists(neighborPos))
            getChunk(neighborPos).buildMesh();
    }
    if (localZ == CHUNK_SIZE_Z-1 || localZ == 0) {
        glm::vec3 neighborPos = glm::vec3(fPos.x, fPos.y, fPos.z - ((localZ == 0) ? 1.f : -1.f));
        if (chunkExists(neighborPos))
            getChunk(neighborPos).buildMesh();
    }
}

