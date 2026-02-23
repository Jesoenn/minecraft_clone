//
// Created by jakub on 18.02.2026.
//

#include "glad/glad.h"
#include "Chunk.h"

// TODO:
// World and Renderer and application uses ChunkManager and chunk.
// Chunk shader used by renderer. - all necessary uniforms are added by it. Then chunkManager.get(0,0).render or something like that

Chunk::Chunk(int posX, int posZ): posX(posX), posZ(posZ), needUpdate(true) {
    // TODO GENEROWANIE PRZENIESC GDZIES INDZIEJ
    generate();
    setUp();
}

void Chunk::buildMesh() {
    for (int x = 0; x<CHUNK_SIZE_X; x++) {
        for (int y = 0; y<CHUNK_SIZE_Y; y++) {
            for (int z = 0; z<CHUNK_SIZE_Z; z++) {
                if (blocks[x][y][z] == BlockType::AIR)
                    continue;

                if (isAir(x+1,y,z))
                    addFace(FaceDirection::RIGHT, x, y, z);

                if (isAir(x-1,y,z))
                    addFace(FaceDirection::LEFT, x, y, z);

                if (isAir(x,y+1,z))
                    addFace(FaceDirection::TOP, x, y, z);

                if (isAir(x,y-1,z))
                    addFace(FaceDirection::BOTTOM, x, y, z);

                if (isAir(x,y,z+1))
                    addFace(FaceDirection::FRONT, x, y, z);

                if (isAir(x,y,z-1))
                    addFace(FaceDirection::BACK, x, y, z);
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

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

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

// TODO THERE IS ONLY 4 VERTICES AND I NEED 6 FOR 2 TRIANGLES
void Chunk::addFace(FaceDirection direction, int x, int y, int z) {
    std::vector<Vertex> vertices;
    if ( direction == FaceDirection::BACK)  {
        vertices = {
            // positions                              // normals                            // tex coords
            {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f}},
{{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
{{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
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
            {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
{{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
{{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
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
            {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},
{{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
{{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
        };
    }

    for (Vertex& vertex : vertices) {
        vertex.pos += glm::vec3(x, y, z);
    }

    verticesMesh.push_back(vertices[0]);
    verticesMesh.push_back(vertices[1]);
    verticesMesh.push_back(vertices[2]);
    verticesMesh.push_back(vertices[2]);
    verticesMesh.push_back(vertices[3]);
    verticesMesh.push_back(vertices[0]);

    // verticesMesh.insert(verticesMesh.end(), vertices.begin(), vertices.end());
}
