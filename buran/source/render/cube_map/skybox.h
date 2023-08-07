#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>

class ResourceSkybox;
class TextureSkybox;

class VertexBuffer;
class IndexBuffer;
class VertexArrayObject;
class Shader;
class RenderContext;

class Skybox {
public:
    Skybox(std::string textureName);
    ~Skybox();

    void Draw(RenderContext ctx);
private:
    VertexArrayObject* vao;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    TextureSkybox* texture;

    Shader* shader;
};

#endif