#include <iostream>

#include "src/core/Application.h"

// TODO
// #2 Add block placing
// #3 Perlin noise
// #4 Infinite terrain generation - adding and removing chunks
// #5 Lighting
// FINISHED

int main() {
    std::cout<<"SHORTCUTS\n"
               "\tTAB - Toggle cursor lock\n"
               "\tF1 - Toggle wireframe mode\n"
               "\tF2 - Toggle physics\n";

    // Create and run game application
    Application app(1600, 900, "Minecraft Clone");
    app.run();

    return 0;
}
