//
// Created by jakub on 18.02.2026.
//

#include "glad/glad.h"
#include "Chunk.h"

// TODO:
// update VBO every block change (needUpdate = true ?)
// verticesMesh has to be Vertex type!
// fix vertex class! - add block location ivec3 xyz in chunk. Renderer will move chunk
// addFace does not know block location - add x,y,z
// addFace doesn't match vertex type. Base it on Vertex. Add movement based on xyz.
// Move enums and vertex class to different files


Chunk::Chunk(int posX, int posZ): posX(posX), posZ(posZ), needUpdate(true) {

}

void Chunk::buildMesh() {
    for (int x = 0; x<CHUNK_SIZE_X; x++) {
        for (int y = 0; y<CHUNK_SIZE_Y; y++) {
            for (int z = 0; z<CHUNK_SIZE_Z; z++) {
                if (blocks[x][y][z] == BlockType::AIR)
                    continue;

                if (isAir(x+1,y,z))
                    addFace(FaceDirection::RIGHT);

                if (isAir(x-1,y,z))
                    addFace(FaceDirection::LEFT);

                if (isAir(x,y+1,z))
                    addFace(FaceDirection::TOP);

                if (isAir(x,y-1,z))
                    addFace(FaceDirection::BOTTOM);

                if (isAir(x,y,z+1))
                    addFace(FaceDirection::FRONT);

                if (isAir(x,y,z-1))
                    addFace(FaceDirection::BACK);
            }
        }
    }

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

    // TODO addFace does not match Vertex struct - TEMP
    glBufferData(GL_ARRAY_BUFFER, verticesMesh.size() * sizeof(Vertex), verticesMesh.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // TODO: add normals and tex coords

    glBindVertexArray(0);
}

void Chunk::generate() {
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                blocks[x][y][z] = BlockType::DIRT;
            }
        }
    }
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

bool Chunk::isAir(int x, int y, int z) {
    return x < 0 || x >= CHUNK_SIZE_X ||
           y < 0 || y >= CHUNK_SIZE_Y ||
           z < 0 || z >= CHUNK_SIZE_Z ||
           blocks[x][y][z] == BlockType::AIR;
}

void Chunk::addFace(FaceDirection direction) {
    std::vector<float> vertices;
    if ( direction == FaceDirection::BACK)  {
        vertices = {
            // positions          // normals          // tex coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        };
    } else if ( direction == FaceDirection::FRONT) {
        vertices = {
            // positions          // normals          // tex coords
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        };
    } else if ( direction == FaceDirection::LEFT) {
        vertices = {
            // positions          // normals          // tex coords
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        };
    } else if ( direction == FaceDirection::RIGHT) {
        vertices = {
            // positions          // normals          // tex coords
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        };
    } else if ( direction == FaceDirection::BOTTOM) {
        vertices = {
            // positions          // normals          // tex coords
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        };
    } else if ( direction == FaceDirection::TOP) {
        vertices = {
            // positions          // normals          // tex coords
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
        };
    }

    verticesMesh.insert(verticesMesh.end(), vertices.begin(), vertices.end());
}
