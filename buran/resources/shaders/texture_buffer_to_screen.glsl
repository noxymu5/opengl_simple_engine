#type vertex
#version 330 core

struct VsOutput {
    vec2 texCoords;
};

#attributes
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
#attributes_end

out VsOutput vsOutput;

void main() {
    gl_Position = vec4(aPos, 1.0);

    vsOutput.texCoords = aTexCoords;
}

#type fragment
#version 330 core

struct VsOutput {
    vec2 texCoords;
};

//vertex shader output
in VsOutput vsOutput;

//shader params
uniform sampler2D textureData;

//output
out vec4 FragColor;

void main() {
    FragColor = texture(textureData, vsOutput.texCoords);
}