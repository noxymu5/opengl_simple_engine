#version 140

in vec2 texCoords;

uniform sampler2D texture0;

out vec4 FragColor;

void main() {
    FragColor = texture(texture0, texCoords);
}