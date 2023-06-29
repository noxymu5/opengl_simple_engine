#type vertex
#version 330 core

#attributes
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
#attributes_end

out vec2 texCoords;

uniform mat4 trf;

void main() {
    gl_Position = trf * vec4(aPos, 1.0);
    texCoords = aTexCoords;
}

#type fragment
#version 330 core

in vec2 texCoords;

uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(uTexture, texCoords);
}