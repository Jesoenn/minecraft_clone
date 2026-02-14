#include <iostream>

#include "src/core/Application.h"

int main() {
    // Create and run game application
    Application app(1600, 900, "Minecraft Clone");
    app.run();

    return 0;
}
