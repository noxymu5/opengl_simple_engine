#ifndef QUAD_H
#define QUAD_H

class VertexBuffer;
class IndexBuffer;
class VertexArrayObject;

class Shader;
class Texture;

class ScreenQuad {
public:
    ScreenQuad();

    void Draw(Shader* shader, Texture* texture);

private:
    VertexArrayObject* vao;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
    
};

#endif