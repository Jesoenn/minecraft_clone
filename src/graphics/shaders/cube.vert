#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//TODO: layout (location = 2) in vec2 aTexCoords;

// TODO: uniform model/view/projection

void main() {
    gl_Position = vec4(aPos, 1.0);
}