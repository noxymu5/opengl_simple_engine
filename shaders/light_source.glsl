#type vertex
#version 330 core

#attributes
layout(location = 0) in vec3 aPos;
#attributes_end

uniform mat4 trf;

void main() {
    gl_Position = trf * vec4(aPos, 1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f);
}