//
// Created by jakub on 15.02.2026.
//

#include "Block.h"

Block::Block(BlockType type):
    type(type) {

}


void Block::setType(BlockType type) {
    this->type = type;
}

BlockType Block::getType() const {
    return type;
}

