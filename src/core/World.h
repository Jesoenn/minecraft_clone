//
// Created by jakub on 16.02.2026.
//

#ifndef WORLD_H
#define WORLD_H
#include "../graphics/Camera.h"
#include "../world/Block.h"
#include "../world/Player.h"

constexpr float GRAVITY = 25.f;
constexpr float JUMP_FORCE = 8.4f;
constexpr float MAX_Y_VELOCITY = 25.f;

class World {
public:
    World();

    void setUp();

    void processMovement(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);
    void processScroll(double yOffset);

    void updatePhysics(float deltaTime);
    void togglePhysics();

    //Setters

    //Getters
    Camera& getCamera();
    std::vector<glm::vec3> getBlockPositions() const;
    BlockType getBlockType(int blockId) const;
    std::vector<Block> getBlocks() const;

private:
    Player player;
    Camera camera;
    std::vector<glm::vec3> blockPositions;
    std::vector<Block> blocks;

    bool physicsEnabled;

    void jumpPhysics(float deltaTime);

    bool checkCollision(glm::vec3 newPos);
    void calcPlayerOnGround();
};



#endif //WORLD_H
