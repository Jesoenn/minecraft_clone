//
// Created by jakub on 16.02.2026.
//

#ifndef WORLD_H
#define WORLD_H
#include "../graphics/Camera.h"
#include "../world/Block.h"


class World {
public:
    World();

    void setUp();

    void processMovement(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);
    void processScroll(double yOffset);

    //Setters


    //Getters
    Camera& getCamera();
    std::vector<glm::vec3> getBlockPositions() const;
    BlockType getBlockType(int blockId) const;
    std::vector<Block> getBlocks() const;

private:
    Camera camera;
    std::vector<glm::vec3> blockPositions;
    std::vector<Block> blocks;
};



#endif //WORLD_H
