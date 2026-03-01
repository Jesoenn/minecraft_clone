#version 330 core

out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;

uniform sampler2D textureAtlas;
uniform vec3 lightDir;
uniform vec3 lightColor;


void main() {

    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightDir);

    float ambient = 0.7;
    float diff = max(dot(norm, -lightDirection), 0.0);
    vec3 lighting = (ambient + diff) * lightColor;

    vec4 texColor = texture(textureAtlas, texCoords);
    fragColor = vec4(texColor.rgb * lighting, texColor.a);
}