#version 330 core

out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;

uniform sampler2D side_texture;
uniform sampler2D top_texture;
uniform sampler2D bottom_texture;


void main() {
    if ( normal.y > 0.5 ) {
        fragColor = texture(top_texture, texCoords);
    } else if ( normal.y < -0.5 ) {
        fragColor = texture(bottom_texture, texCoords);
    } else {
        fragColor = texture(side_texture, texCoords);
    }
}