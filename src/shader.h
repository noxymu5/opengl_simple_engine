#ifndef SHADER
#define SHADER

#include "common.h"

class Shader
{
public:
    Shader();
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