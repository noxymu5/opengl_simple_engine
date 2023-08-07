#pragma once

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