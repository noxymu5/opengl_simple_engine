#version 140

in vec3 aPos;
in vec2 aTexCoords; 

out vec3 vertexColor;
out vec2 texCoords;

void main() {
    gl_Position = vec4(aPos, 1.0);
    texCoords = aTexCoords;
}