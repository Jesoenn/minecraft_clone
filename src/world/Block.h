//
// Created by jakub on 15.02.2026.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <vector>

#include "../graphics/Shader.h"

enum class BlockType {
    AIR,
    DIRT,
    GRASS_BLOCK
};

class Block {
public:
    explicit Block(BlockType type);

    // Setters
    void setType(BlockType type);

    // Getters
    BlockType getType() const;

private:
    BlockType type;

};



#endif //BLOCK_H
