#type vertex
#version 330 core

struct VsOutput {
    vec3 texCoords;
};

#attributes
layout(location = 0) in vec3 aPos;
#attributes_end

out VsOutput vsOutput;

uniform mat4 uViewProj;

void main() {
    vsOutput.texCoords = aPos;
    vsOutput.texCoords.y = -vsOutput.texCoords.y;
    vsOutput.texCoords.x = -vsOutput.texCoords.x;
    
    vec4 pos = uViewProj * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}

#type fragment
#version 330 core

struct VsOutput {
    vec3 texCoords;
};

//vertex shader output
in VsOutput vsOutput;

//shader params
uniform samplerCube textureData;

//output
out vec4 FragColor;

void main() {
    FragColor = texture(textureData, vsOutput.texCoords);
}