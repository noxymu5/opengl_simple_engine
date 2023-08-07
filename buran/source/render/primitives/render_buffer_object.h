#ifndef RENDER_BUFFER_OBJECT_H
#define RENDER_BUFFER_OBJECT_H

class RenderBufferObject {
public:
    RenderBufferObject(unsigned int width, unsigned int height);
    ~RenderBufferObject();

    void Bind();
    void UnBind();
    unsigned int Id() { return id; }

private:
    unsigned int id;
};

#endif