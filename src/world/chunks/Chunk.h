//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNK_H
#define CHUNK_H

#include "../../graphics/BlockTextureAtlas.h"
#include "../Block.h"
#include "../../util/FaceDirection.h"
#include <array>

const int CHUNK_SIZE_X = 16;
const int CHUNK_SIZE_Y = 16;
const int CHUNK_SIZE_Z = 16;

struct Vertex {
    glm::vec3 pos;      // Vertex position + chunk local offset (x,y,z)
    glm::vec3 normal;
    glm::vec2 texCoords;    // Texture coordinates + offset based on block type
};

class Chunk {
public:
    Chunk(int posX, int posZ, BlockTextureAtlas& texAtlas, std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>,
        CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks, std::function<bool(int,int,int)> isGlobalAir);

    void setUp();
    void buildMesh();
    void render();

    // Setters
    void setBlock(glm::ivec3 pos, BlockType block);

    // Getters
    BlockType getBlock(glm::ivec3 pos);
    glm::ivec2 getPosition();
    std::vector<Vertex>& getMesh();
    std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> getBlocks();

private:
    int posX, posZ;
    std::array<std::array< std::array<BlockType, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks;
    std::vector<Vertex> verticesMesh;

    unsigned int VAO, VBO;
    BlockTextureAtlas& texAtlas;

    bool needUpdate; // TODO WHEN BLOCK PLACING/DESTROYING IS ADDED

    bool isAir(int x, int y, int z); // Check if block is air. True if out of bounds - x<0; x>=chunk_size_x etc.
    std::function<bool(int,int,int)> isGlobalAir;
    void addFace(FaceDirection direction, int x, int y, int z, BlockType type); // Adds face to mesh - 6 vertices, 2 triangles.

    glm::vec2 getTextureOffset(BlockType type, FaceDirection direction);
};



#endif //CHUNK_H
