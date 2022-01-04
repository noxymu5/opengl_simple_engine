#ifndef SHADER
#define SHADER

#include <string>
#include <fstream>
#include <iostream>

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath, GLsizei inStride);

    unsigned int GetProgramId() const { return shaderProgramId; }
    void Use();

    void SetVertexAttribute(std::string name, GLint size, GLenum type, GLboolean isNormalized, unsigned int offset);

    void SetUniform(std::string name, float value);
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, glm::mat4* matrix);

private:
    unsigned int shaderProgramId;
    GLsizei stride;

    char* LoadCodeFromFile(std::string FilePath);
    unsigned int CreateAndCompileShader(GLenum shaderType, char* shaderCode);
};

#endif