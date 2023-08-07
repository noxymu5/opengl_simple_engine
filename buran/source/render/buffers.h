#pragma once

class Texture;
class RenderBufferObject;

class VertexBuffer {
private:
    unsigned int id;

public:
    VertexBuffer(const float* verticesData, const unsigned int size);
    VertexBuffer(void* verticesData, const unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};

class IndexBuffer {
private:
    unsigned int id;
    unsigned int count;

public:
    IndexBuffer(const unsigned int* indices, unsigned int size);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;
    unsigned int GetCount();
};

enum class FrameBufferBindType {
    READ,
    WRITE,
    READ_AND_WRITE
};

enum class FrameBufferAttachmentType {
    COLOR,
    DEPTH,
    STENCIL,
    DEPTH_STENCIL
};

namespace gl {
    enum class GLenum : unsigned int;
}

class FrameBuffer {
public:
    FrameBuffer(FrameBufferBindType bindType = FrameBufferBindType::READ_AND_WRITE);
    ~FrameBuffer();

    void Attach(Texture* tex, FrameBufferAttachmentType attachmentType);
    void Attach(RenderBufferObject* tex, FrameBufferAttachmentType attachmentType);

    void Bind();
    void Unbind();

    void Validate();
private:
    unsigned int id;
    gl::GLenum bindType;

    gl::GLenum GetGlAttachmentType(FrameBufferAttachmentType attachmentType);
};