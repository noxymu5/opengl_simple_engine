#include "buffers.h"

#include <GLEW/glew.h>

#include "core/asserts.h"
#include "render/texture/texture.h"
#include "render/primitives/render_buffer_object.h"

//Vertex buffer

VertexBuffer::VertexBuffer(const float* verticesData, const unsigned int size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, verticesData, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(void* verticesData, const unsigned int size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, verticesData, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Index buffer

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int size) {
    count = size / sizeof(unsigned int);

    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

unsigned int IndexBuffer::GetCount() {
    return count;
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Frame buffer

FrameBuffer::FrameBuffer(FrameBufferBindType target) {
    switch (target)
    {
    case FrameBufferBindType::READ:
        bindType = GL_READ_FRAMEBUFFER;
        break;
    case FrameBufferBindType::WRITE:
        bindType = GL_DRAW_FRAMEBUFFER;
        break;
    case FrameBufferBindType::READ_AND_WRITE:
        bindType = GL_FRAMEBUFFER;
        break;
    default:
        ASSERT_FAIL("Unknown frame buffer bind type")
        break;
    }

    glGenFramebuffers(1, &id);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &id);
}

void FrameBuffer::Attach(Texture* tex, FrameBufferAttachmentType attachmentType) {
    unsigned int glAttachmentType = GetGlAttachmentType(attachmentType);

    glFramebufferTexture2D(bindType, glAttachmentType, GL_TEXTURE_2D, tex->Id(), 0);
}

void FrameBuffer::Attach(RenderBufferObject* rbo, FrameBufferAttachmentType attachmentType) {
    unsigned int glAttachmentType = GetGlAttachmentType(attachmentType);

    glFramebufferRenderbuffer(bindType, glAttachmentType, GL_RENDERBUFFER, rbo->Id());
}

void FrameBuffer::Bind() {
    glBindFramebuffer(bindType, id);
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(bindType, 0);
}

void FrameBuffer::Validate() {
    GLenum status = glCheckFramebufferStatus(bindType);

    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE:
        return;
        break;
    case GL_FRAMEBUFFER_UNDEFINED:
        ASSERT_FAIL("Specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist")
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        ASSERT_FAIL("Some of the framebuffer attachment points are framebuffer incomplete")
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        ASSERT_FAIL("Framebuffer does not have at least one image attached to it")
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        ASSERT_FAIL("The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi")
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        ASSERT_FAIL("GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER")
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        ASSERT_FAIL("Combination of internal formats of the attached images violates an implementation-dependent set of restrictions")
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        ASSERT_FAIL("The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES")
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        ASSERT_FAIL(" Some framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target")
        break;
    default:
        ASSERT_FAIL("Unknown framebuffer error")
        break;
    }
}

unsigned int FrameBuffer::GetGlAttachmentType(FrameBufferAttachmentType attachmentType) {
    unsigned int glAttachmentType;

    switch (attachmentType)
    {
    case FrameBufferAttachmentType::COLOR:
        glAttachmentType = GL_COLOR_ATTACHMENT0;
        break;
    case FrameBufferAttachmentType::DEPTH:
        glAttachmentType = GL_DEPTH_ATTACHMENT;
        break;
    case FrameBufferAttachmentType::STENCIL:
        glAttachmentType = GL_STENCIL_ATTACHMENT;
        break;
    case FrameBufferAttachmentType::DEPTH_STENCIL:
        glAttachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
        break;    
    default:
        ASSERT_FAIL("Unknown frame buffer attachment type")
        break;
    }

    return glAttachmentType;
}