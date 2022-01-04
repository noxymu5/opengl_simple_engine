#ifndef SHADER
#define SHADER

#include <string>
#include <fstream>
#include <iostream>

#include <GLEW/glew.h>

class Shader
{
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

    unsigned int GetProgramId() const { return shaderProgramId; }
    void Use();

private:
    unsigned int shaderProgramId;

    char* LoadCodeFromFile(std::string FilePath);
    unsigned int CreateAndCompileShader(GLenum shaderType, char* shaderCode);
};

#endif