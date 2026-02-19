//
// Created by jakub on 18.02.2026.
//

#ifndef CHUNK_H
#define CHUNK_H

#include "../Block.h"

constexpr int SIZE = 16;

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 textureCoords;
    BlockType type;
};

class Chunk {
public:
    Chunk(glm::ivec3 pos);

    void buildMesh();

    // Setters
    void setBlock(glm::ivec3 pos, BlockType block);

    // Getters
    Block getBlock(glm::ivec3 pos);
    glm::ivec3 getPosition();
    std::vector<Vertex>& getMesh();

private:
    glm::ivec3 pos;
    std::vector<BlockType> blocks;
    std::vector<Vertex> verticesMesh;

    // Czy przechowywac wierzcholki, czy zrobic klase ktora ma "kwadraty"
    // jak odbywa sie proces rysowania - skad gpu wie jak przeniesc kazdy wierzcholek
    unsigned int VAO, VBO;

    int posToIndex(glm::ivec3 pos);

};



#endif //CHUNK_H
