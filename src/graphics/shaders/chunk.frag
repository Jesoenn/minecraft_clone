#version 330 core

out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;

uniform sampler2D texture;


void main() {
//    fragColor = texture(top_texture, texCoords);
    fragColor = vec4(0.5, 0.5, 0.5, 1.0);
}