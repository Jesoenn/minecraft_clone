//
// Created by jakub on 16.02.2026.
//

#ifndef WORLD_H
#define WORLD_H
#include "../graphics/Camera.h"


class World {
public:
    World();
    void setUp();

    Camera& getCamera();

private:
    Camera camera;
};



#endif //WORLD_H
