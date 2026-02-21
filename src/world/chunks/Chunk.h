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
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;
    // BlockType type;
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
    void addFace(FaceDirection direction); // Adds face to mesh - 6 vertices, 2 triangles. TODO: add parameters - direction, texture


    // Czy przechowywac wierzcholki, czy zrobic klase ktora ma "kwadraty"
    // jak odbywa sie proces rysowania - skad gpu wie jak przeniesc kazdy wierzcholek
    unsigned int VAO, VBO;

};



#endif //CHUNK_H
