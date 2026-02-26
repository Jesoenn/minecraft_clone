#version 330 core

out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;

uniform sampler2D textureAtlas;


void main() {
    fragColor = texture(textureAtlas, texCoords);
}