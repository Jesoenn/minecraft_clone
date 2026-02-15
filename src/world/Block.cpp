//
// Created by jakub on 15.02.2026.
//

#include "Block.h"

Block::Block(BlockType type): type(type) {
}

BlockType Block::getType() {
    return type;
}

void Block::setType(BlockType type) {
    this->type = type;
}
