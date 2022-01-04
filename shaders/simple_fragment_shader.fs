#version 140

in vec2 texCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixFactor;

out vec4 FragColor;

void main() {
    FragColor = mix(texture(texture0, texCoords), texture(texture1, texCoords), mixFactor);
}