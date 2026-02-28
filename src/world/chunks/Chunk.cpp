//
// Created by jakub on 18.02.2026.
//

#include "glad/glad.h"
#include "Chunk.h"

#include <utility>

Chunk::Chunk(int posX, int posZ, BlockTextureAtlas& texAtlas, std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks, std::function<bool(int,int,int)> isGlobalAir):
    posX(posX), posZ(posZ), blocks(blocks), texAtlas(texAtlas), needUpdate(true), isGlobalAir(std::move(isGlobalAir)) {
    setUp();
}

void Chunk::buildMesh() {
    verticesMesh.clear();
    for (int x = 0; x<CHUNK_SIZE_X; x++) {
        for (int y = 0; y<CHUNK_SIZE_Y; y++) {
            for (int z = 0; z<CHUNK_SIZE_Z; z++) {
                BlockType type = blocks[x][y][z];
                if (type == BlockType::AIR)
                    continue;

                if (isAir(x+1,y,z))
                    addFace(FaceDirection::RIGHT, x, y, z, type);

                if (isAir(x-1,y,z))
                    addFace(FaceDirection::LEFT, x, y, z, type);

                if (isAir(x,y+1,z))
                    addFace(FaceDirection::TOP, x, y, z, type);

                if (isAir(x,y-1,z))
                    addFace(FaceDirection::BOTTOM, x, y, z, type);

                if (isAir(x,y,z+1))
                    addFace(FaceDirection::FRONT, x, y, z, type);

                if (isAir(x,y,z-1))
                    addFace(FaceDirection::BACK, x, y, z, type);
            }
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesMesh.size() * sizeof(Vertex), verticesMesh.data(), GL_STATIC_DRAW);

    needUpdate = false;
}

void Chunk::render() {
    if ( needUpdate )
        buildMesh();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(verticesMesh.size()));
}

void Chunk::setUp() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, verticesMesh.size() * sizeof(Vertex), verticesMesh.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Chunk::setBlock(glm::ivec3 pos, BlockType block) {
    blocks[pos.x][pos.y][pos.z] = block;
}

BlockType Chunk::getBlock(glm::ivec3 pos) {
    return blocks[pos.x][pos.y][pos.z];
}

glm::ivec2 Chunk::getPosition() {
    return {posX, posZ};
}

std::vector<Vertex> & Chunk::getMesh() {
    return verticesMesh;
}

std::array<std::array<std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> Chunk::getBlocks() {
    return blocks;
}

bool Chunk::isAir(int x, int y, int z) {
    if ( y < 0 || y >= CHUNK_SIZE_Y )
        return true;

    if (x < 0 || x >= CHUNK_SIZE_X || z < 0 || z >= CHUNK_SIZE_Z) {
        return isGlobalAir(x + posX, y, z + posZ);
    }

    return blocks[x][y][z] == BlockType::AIR;
}

void Chunk::addFace(FaceDirection direction, int x, int y, int z, BlockType type) {
    std::vector<Vertex> vertices;
    if ( direction == FaceDirection::BACK)  {
        vertices = {
            // positions                              // normals                            // tex coords
            {{0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f}},
            {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
        };
    } else if ( direction == FaceDirection::FRONT) {
        vertices = {
            // positions                             // normals                            // tex coords
            {{-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
            {{0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
        };
    } else if ( direction == FaceDirection::LEFT) {
        vertices = {
            // positions                              // normals                            // tex coords
            {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
        };
    } else if ( direction == FaceDirection::RIGHT) {
        vertices = {
            // positions                             // normals                            // tex coords
            {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
        };
    } else if ( direction == FaceDirection::BOTTOM) {
        vertices = {
            // positions                             // normals                             // tex coords
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
        };
    } else if ( direction == FaceDirection::TOP) {
        vertices = {
            // positions                             // normals                            // tex coords
            {{0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
        };
    }

    for (Vertex& vertex : vertices) {
        vertex.pos += glm::vec3(x, y, z);
        // Normalize texture coords to one block texture size and add offset
        vertex.texCoords /= texAtlas.getAtlasSize();
        vertex.texCoords *= texAtlas.blockTexSize;
        vertex.texCoords += getTextureOffset(type, direction);
    }
    verticesMesh.insert(verticesMesh.end(), vertices.begin(), vertices.end());
}

glm::vec2 Chunk::getTextureOffset(BlockType type, FaceDirection direction) {
    return texAtlas.getTextureCoords(type, direction);
}
