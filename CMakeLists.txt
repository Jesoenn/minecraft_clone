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
        src/core/Window.h)

# Add DLLs (libraries)
target_link_libraries(minecraft_clone
        glfw3dll
        opengl32
)
