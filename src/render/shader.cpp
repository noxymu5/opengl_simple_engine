#include "shader.h"

#include <GLEW/glew.h>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <sstream>

#include "core/asserts.h"
#include "resource_system/loader/shader_loader.h"

static const std::unordered_map<std::string, VertexBufferLayoutTypeInfo> typeToLayoutMap = {
    {"vec2", {GL_FLOAT, 2, sizeof(float) * 2}},
    {"vec3", {GL_FLOAT, 3, sizeof(float) * 3}}
};

Shader::Shader(const std::string &path) {
    ShaderLoader loader(path);
    ResourceShader resource = loader.Get();

    CreateAttributreLayout(resource);
    CompileShaderProgram(resource.shaderSources);
}

void Shader::Use() {
    glUseProgram(shaderProgramId);
}

void Shader::BindVertexAttributes() {
    unsigned int currentOffset = 0;
    for(int i = 0; i < typesLayout.size(); ++i) {
        VertexBufferLayoutTypeInfo& info = typesLayout[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, info.count, info.type, GL_FALSE, stride, (void*)currentOffset);
        currentOffset += info.size;
    }
}

void Shader::SetUniform(std::string name, float value) {
    int uniformLocation = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1f(uniformLocation, value);
}

void Shader::SetUniform(std::string name, int value) {
    int uniformLocation = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1i(uniformLocation, value);
}

void Shader::SetUniform(std::string name, const glm::mat4& matrix) {
    int uniformLocation = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
};

void Shader::SetUniform(std::string name, const glm::vec3& vector) {
    int uniformLocation = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
};

void Shader::CreateAttributreLayout(ResourceShader resource) {
    for (auto& attributeType: resource.attributeTypes) {
        auto it = typeToLayoutMap.find(attributeType);
        ASSERT(it != typeToLayoutMap.end(), "Unknown attribute type %s", attributeType.c_str())

        PushLayout(it->second);
    }
}

void Shader::PushLayout(VertexBufferLayoutTypeInfo info) {
    typesLayout.push_back(info);
    stride += info.size;
}

void Shader::CompileShaderProgram(std::string* shaderSources) {
    shaderProgramId = glCreateProgram();
    
    int shaderIds[(int)ShaderType::Count];
    for(int shaderType = 0; shaderType < (int)ShaderType::Count; ++shaderType) {
        if (shaderSources[shaderType].empty()) {
            shaderIds[shaderType] = -1;
            continue;
        }

        unsigned int shaderId = CreateAndCompileShader((ShaderType)shaderType, shaderSources[shaderType].c_str());
        glAttachShader(shaderProgramId, shaderId);

        shaderIds[shaderType] = shaderId;
    }

    glLinkProgram(shaderProgramId);

    int success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    for(int idx = 0; idx < (int)ShaderType::Count; ++idx) {
        if (shaderIds[idx] > 0) {
            glDeleteShader(shaderIds[idx]);
        }
    }
}

unsigned int Shader::CreateAndCompileShader(ShaderType shaderType, const char* shaderCode) {
    GLenum glShaderType;
    switch (shaderType)
    {
    case ShaderType::Vertex:
        glShaderType = GL_VERTEX_SHADER;
        break;
    case ShaderType::Fragment:
        glShaderType = GL_FRAGMENT_SHADER;
        break;
    
    default:
        break;
    }
    
    unsigned int shaderId;
    shaderId = glCreateShader(glShaderType);
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        
        const char* shaderTypeString = glShaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << shaderTypeString << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    return shaderId;
}