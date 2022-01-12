#include "shader.h"

#include <string>
#include <unordered_map>
#include <iterator>
#include <sstream>

static const std::unordered_map<std::string, VertexBufferLayoutTypeInfo> typeToLayoutMap = {
    {"vec2", {GL_FLOAT, 2, sizeof(float) * 2}},
    {"vec3", {GL_FLOAT, 3, sizeof(float) * 3}}
};

Shader::Shader(const std::string &path) {
    std::string* shaderSources = ParseShaderSources(path);
    CompileShaderProgram(shaderSources);
    
    delete[] shaderSources;
}

void Shader::Use() {
    glUseProgram(shaderProgramId);
}

void Shader::BindVertexAttributes() {
    unsigned int currentOffset = 0;
    for(int i = 0; i < typesLayout.size(); ++i) {
        VertexBufferLayoutTypeInfo& info = typesLayout[i];

        glVertexAttribPointer(i, info.count, info.type, GL_FALSE, stride, (void*)currentOffset);
        glEnableVertexAttribArray(i);
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

std::string Shader::LoadCodeFromFile(std::string filePath) {
    std::ifstream fileStream;
    fileStream.exceptions (std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
    
    try {
        fileStream.open(filePath, std::ifstream::binary);	
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPENED - " << e.what() << std::endl;
    }

    fileStream.seekg (0, fileStream.end);
    int fileLength = fileStream.tellg();
    fileStream.seekg (0, fileStream.beg);

    std::stringstream shaderSourceStream;
    try {
        shaderSourceStream << fileStream.rdbuf();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ - " << e.what() << std::endl;
    }

    fileStream.close();

    return shaderSourceStream.str();
}

std::string* Shader::ParseShaderSources(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile) {
        std::cout << "Can not open file by path " << filePath.c_str() << "\n";
        return nullptr;
    }

    ShaderType type;
    std::string line;
    bool isAttributeSection = false;
    
    std::string* shaderSources = new std::string[(int)(ShaderType::Count)];
    while (getline(shaderFile, line)) {
        if (line.find("#type") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::Fragment;
            } else {
                std::cout << "Undefined shader type in string: " << line << "\n";
            }

            continue;
        }

        if (!isAttributeSection && line.find("#attributes") != std::string::npos) {
            isAttributeSection = true;
            continue;
        } else if (isAttributeSection && line.find("attributes_end") != std::string::npos) {
            isAttributeSection = false;
            continue;
        }

        shaderSources[(int)type].append(line + "\n");

        if (isAttributeSection) {
            for (auto& it: typeToLayoutMap) {
                if (line.find(it.first) != std::string::npos){
                    PushLayout(it.second);
                }
            }    
        }
    }

    return shaderSources;
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