#include <iostream>

#include "src/core/Application.h"

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
