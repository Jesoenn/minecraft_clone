#version 330 core
layout(location = 0) in vec2 aPos;

uniform vec2 windowSize;

void main(){
    vec2 pos = aPos / (windowSize);
    gl_Position = vec4(pos, 0.0, 1.0);
}

