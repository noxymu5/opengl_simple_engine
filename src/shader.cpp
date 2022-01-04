#include "shader.h"

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath, GLsizei inStride) : stride(inStride) {
    char* vertexShaderCode = LoadCodeFromFile(vertexShaderPath);
    char* fragmentShaderCode = LoadCodeFromFile(fragmentShaderPath);

    unsigned int vertexShader = CreateAndCompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    unsigned int fragmentShader = CreateAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    delete[] vertexShaderCode;
    delete[] fragmentShaderCode;

    shaderProgramId = glCreateProgram();

    glAttachShader(shaderProgramId, vertexShader);
    glAttachShader(shaderProgramId, fragmentShader);
    glLinkProgram(shaderProgramId);

    int success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(shaderProgramId);
}

char* Shader::LoadCodeFromFile(std::string filePath) {
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
    char* shaderCode = new char[fileLength + 1];

    try {
        fileStream.read(shaderCode, fileLength);
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ - " << e.what() << std::endl;
    }

    shaderCode[fileLength] = '\0';
    fileStream.close();

    return shaderCode;
}

unsigned int Shader::CreateAndCompileShader(GLenum shaderType, char* shaderCode) {
    unsigned int shaderId;
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        
        const char* shaderTypeString = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << shaderTypeString << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    return shaderId;
}

void Shader::SetVertexAttribute(std::string name, GLint size, GLenum type, GLboolean isNormalized, unsigned int offset) {
    int attributeLocation = glGetAttribLocation(shaderProgramId, name.c_str());
    glVertexAttribPointer(attributeLocation, size, type, isNormalized, stride, (void*)offset);
    glEnableVertexAttribArray(attributeLocation);
}

void Shader::SetUniform(std::string name, float value) {
    int uniformLocation = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1f(uniformLocation, value);
}

void Shader::SetUniform(std::string name, int value) {
    int uniformLocation = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1i(uniformLocation, value);
}