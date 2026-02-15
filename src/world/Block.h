//
// Created by jakub on 15.02.2026.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <vector>

#include "../graphics/Shader.h"

enum class BlockType {
    AIR,
    DIRT
};

class Block {
public:
    Block(BlockType type);

    // Getters
    BlockType getType();

    // Setters
    void setType(BlockType type);

private:
    BlockType type;


};



#endif //BLOCK_H
