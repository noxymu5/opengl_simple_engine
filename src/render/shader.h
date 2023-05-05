#ifndef SHADER
#define SHADER

#include <vector>
#include <string>

#include "core/glm_declarations.h"

class ResourceShader;
enum class ShaderType;

struct VertexBufferLayoutTypeInfo {
    unsigned int type;
    unsigned int count;
    unsigned int size;
};

class Shader {
public:
    Shader(const std::string &path);

    unsigned int GetProgramId() const { return shaderProgramId; }
    void Use();

    void BindVertexAttributes();

    void SetUniform(std::string name, float value);
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, const glm::mat4& matrix);
    void SetUniform(std::string name, const glm::vec3& vector);

private:
    unsigned int shaderProgramId;

    std::vector<VertexBufferLayoutTypeInfo> typesLayout;
    unsigned int stride = 0;

    void CreateAttributreLayout(ResourceShader resource);

    void PushLayout(VertexBufferLayoutTypeInfo info);

    void CompileShaderProgram(std::string* shaderSources);
    unsigned int CreateAndCompileShader(ShaderType shaderType, const char* shaderCode);
};

#endif