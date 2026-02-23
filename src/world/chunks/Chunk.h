//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNK_H
#define CHUNK_H

#include "../Block.h"

const int CHUNK_SIZE_X = 16;
const int CHUNK_SIZE_Y = 16;
const int CHUNK_SIZE_Z = 16;

enum class FaceDirection {
    FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM
};

struct Vertex {
    glm::vec3 pos;      // Vertex position + chunk local offset (x,y,z)
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Chunk {
public:
    Chunk(int posX, int posZ);

    void setUp();
    void buildMesh();
    void render();  // TODO: render as dirt. Now impossible for other blocks.
    void generate();

    // Setters
    void setBlock(glm::ivec3 pos, BlockType block);

    // Getters
    BlockType getBlock(glm::ivec3 pos);
    glm::ivec2 getPosition();
    std::vector<Vertex>& getMesh();

private:
    int posX, posZ;
    BlockType blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

    std::vector<Vertex> verticesMesh;

    bool needUpdate; // TODO WHEN BLOCK PLACING/DESTROYING IS ADDED


    bool isAir(int x, int y, int z); // Check if block is air. True if out of bounds - x<0; x>=chunk_size_x etc.
    void addFace(FaceDirection direction, int x, int y, int z); // Adds face to mesh - 6 vertices, 2 triangles. TODO: add parameters - texture

    unsigned int VAO, VBO;
};



#endif //CHUNK_H
