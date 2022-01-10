#ifndef SHADER
#define SHADER

#include "common.h"
#include <vector>

enum class ShaderType {
    Udefined = -1,
    Vertex,
    Fragment,

    Count
};

struct VertexBufferLayoutTypeInfo {
    GLenum type;
    unsigned int count;
    GLsizei size;
};

class Shader {
public:
    Shader(const std::string &path);

    unsigned int GetProgramId() const { return shaderProgramId; }
    void Use();

    void BindVertexAttributes();

    void SetUniform(std::string name, float value);
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, glm::mat4* matrix);

private:
    unsigned int shaderProgramId;

    std::vector<VertexBufferLayoutTypeInfo> typesLayout;
    GLsizei stride = 0;

    std::string* ParseShaderSources(const std::string& filePath);
    std::string LoadCodeFromFile(std::string FilePath);

    void PushLayout(VertexBufferLayoutTypeInfo info);

    void CompileShaderProgram(std::string* shaderSources);
    unsigned int CreateAndCompileShader(ShaderType shaderType, const char* shaderCode);
};

#endif