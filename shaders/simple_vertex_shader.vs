#version 140

in vec3 aPos;
in vec2 aTexCoords; 

out vec2 texCoords;

uniform mat4 trf;

void main() {
    gl_Position = trf * vec4(aPos, 1.0);
    texCoords = aTexCoords;
}