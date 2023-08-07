#include "shader.h"

#include <glbinding/gl/gl.h>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <sstream>

#include "core/asserts.h"
#include "core/logging.h"
#include "resource_system/loader/shader_loader.h"

static const std::unordered_map<std::string, VertexBufferLayoutTypeInfo> typeToLayoutMap = {
    {"vec2", {gl::GL_FLOAT, 2, sizeof(float) * 2}},
    {"vec3", {gl::GL_FLOAT, 3, sizeof(float) * 3}}
};

Shader::Shader(ResourceShader* resource) {
    CreateAttributreLayout(*resource);
    CompileShaderProgram(resource->shaderSources);
}

void Shader::Use() {
    gl::glUseProgram(shaderProgramId);
}

void Shader::BindVertexAttributes() {
    unsigned int currentOffset = 0;
    for(int i = 0; i < typesLayout.size(); ++i) {
        VertexBufferLayoutTypeInfo& info = typesLayout[i];

        gl::glEnableVertexAttribArray(i);
        gl::glVertexAttribPointer(i, info.count, (gl::GLenum)info.type, gl::GL_FALSE, stride, (void*)currentOffset);
        currentOffset += info.size;
    }
}

void Shader::SetUniform(std::string name, float value) {
    int uniformLocation = gl::glGetUniformLocation(shaderProgramId, name.c_str());
    gl::glUniform1f(uniformLocation, value);
}

void Shader::SetUniform(std::string name, int value) {
    int uniformLocation = gl::glGetUniformLocation(shaderProgramId, name.c_str());
    gl::glUniform1i(uniformLocation, value);
}

void Shader::SetUniform(std::string name, const glm::mat4& matrix) {
    int uniformLocation = gl::glGetUniformLocation(shaderProgramId, name.c_str());
    gl::glUniformMatrix4fv(uniformLocation, 1, gl::GL_FALSE, glm::value_ptr(matrix));
};

void Shader::SetUniform(std::string name, const glm::vec3& vector) {
    int uniformLocation = gl::glGetUniformLocation(shaderProgramId, name.c_str());
    gl::glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
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
    shaderProgramId = gl::glCreateProgram();
    
    int shaderIds[(int)ShaderType::Count];
    for(int shaderType = 0; shaderType < (int)ShaderType::Count; ++shaderType) {
        if (shaderSources[shaderType].empty()) {
            shaderIds[shaderType] = -1;
            continue;
        }

        unsigned int shaderId = CreateAndCompileShader((ShaderType)shaderType, shaderSources[shaderType].c_str());
        gl::glAttachShader(shaderProgramId, shaderId);

        shaderIds[shaderType] = shaderId;
    }

    gl::glLinkProgram(shaderProgramId);

    int success;
    gl::glGetProgramiv(shaderProgramId, gl::GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        gl::glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
        LOG("Shader program compilation failed:\n %s", infoLog)
    }

    for(int idx = 0; idx < (int)ShaderType::Count; ++idx) {
        if (shaderIds[idx] > 0) {
            gl::glDeleteShader(shaderIds[idx]);
        }
    }
}

unsigned int Shader::CreateAndCompileShader(ShaderType shaderType, const char* shaderCode) {
    gl::GLenum glShaderType;
    switch (shaderType)
    {
    case ShaderType::Vertex:
        glShaderType = gl::GL_VERTEX_SHADER;
        break;
    case ShaderType::Fragment:
        glShaderType = gl::GL_FRAGMENT_SHADER;
        break;
    
    default:
        break;
    }
    
    unsigned int shaderId;
    shaderId = glCreateShader(glShaderType);
    gl::glShaderSource(shaderId, 1, &shaderCode, NULL);
    gl::glCompileShader(shaderId);

    int success;
    gl::glGetShaderiv(shaderId, gl::GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        gl::glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        
        const char* shaderTypeString = glShaderType == gl::GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        LOG("Shader %s compilation failed:\n %s", shaderTypeString, infoLog)
    };

    return shaderId;
}