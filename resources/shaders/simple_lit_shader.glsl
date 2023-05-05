#type vertex
#version 330 core

#attributes
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormal;
#attributes_end

out vec2 texCoords;
out vec3 outNormal;
out vec3 FragPos;

uniform mat4 viewProj;
uniform mat4 model;

void main() {
    gl_Position = viewProj * model * vec4(aPos, 1.0);
    texCoords = aTexCoords;
    outNormal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0f));
}

#type fragment
#version 330 core

in vec2 texCoords;
in vec3 outNormal;
in vec3 FragPos;

uniform sampler2D uTexture;
uniform vec3 ulightColor;
uniform vec3 ulightPos;
uniform vec3 uViewPos;

out vec4 FragColor;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * ulightColor;

    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(ulightPos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ulightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * ulightColor;

    vec4 res = vec4((ambient + diffuse + specular) , 1.0f);
    FragColor = res * texture(uTexture, texCoords);
}