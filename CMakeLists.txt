cmake_minimum_required(VERSION 3.30)
project(minecraft_clone)

set(CMAKE_CXX_STANDARD 23)

# Add headers
include_directories(include)
# Link libraries
link_directories(lib)

add_executable(minecraft_clone main.cpp
        src/glad.c
        src/core/Application.cpp
        src/core/Application.h
        src/core/Window.cpp
        src/core/Window.h
        src/graphics/Renderer.cpp
        src/graphics/Renderer.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/world/Block.cpp
        src/world/Block.h
        src/graphics/Camera.cpp
        src/graphics/Camera.h
        src/core/World.cpp
        src/core/World.h
        src/core/InputManager.cpp
        src/core/InputManager.h
        src/graphics/Texture.cpp
        src/graphics/Texture.h
        src/graphics/BlockTextureAtlas.cpp
        src/graphics/BlockTextureAtlas.h
        src/world/Player.cpp
        src/world/Player.h
        src/world/chunks/Chunk.cpp
        src/world/chunks/Chunk.h
        src/world/chunks/ChunkManager.cpp
        src/world/chunks/ChunkManager.h)

# Add DLLs (libraries)
target_link_libraries(minecraft_clone
        glfw3dll
        opengl32
)
