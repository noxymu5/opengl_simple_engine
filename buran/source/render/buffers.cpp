#include "buffers.h"

#include <glbinding/gl/gl.h>

#include "core/asserts.h"
#include "render/texture/texture.h"
#include "render/primitives/render_buffer_object.h"

//Vertex buffer

VertexBuffer::VertexBuffer(const float* verticesData, const unsigned int size) {
    gl::glGenBuffers(1, &id);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, id);
    gl::glBufferData(gl::GL_ARRAY_BUFFER, size, verticesData, gl::GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(void* verticesData, const unsigned int size) {
    gl::glGenBuffers(1, &id);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, id);
    gl::glBufferData(gl::GL_ARRAY_BUFFER, size, verticesData, gl::GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    gl::glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind() const {
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, id);
}

void VertexBuffer::UnBind() const {
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
}

//Index buffer

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int size) {
    count = size / sizeof(unsigned int);

    gl::glGenBuffers(1, &id);
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, id);
    gl::glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER, size, indices, gl::GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    gl::glDeleteBuffers(1, &id);
}

unsigned int IndexBuffer::GetCount() {
    return count;
}

void IndexBuffer::Bind() const {
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::UnBind() const {
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Frame buffer

FrameBuffer::FrameBuffer(FrameBufferBindType target) {
    switch (target)
    {
    case FrameBufferBindType::READ:
        bindType = gl::GL_READ_FRAMEBUFFER;
        break;
    case FrameBufferBindType::WRITE:
        bindType = gl::GL_DRAW_FRAMEBUFFER;
        break;
    case FrameBufferBindType::READ_AND_WRITE:
        bindType = gl::GL_FRAMEBUFFER;
        break;
    default:
        ASSERT_FAIL("Unknown frame buffer bind type")
        break;
    }

    gl::glGenFramebuffers(1, &id);
}

FrameBuffer::~FrameBuffer() {
    gl::glDeleteFramebuffers(1, &id);
}

void FrameBuffer::Attach(Texture* tex, FrameBufferAttachmentType attachmentType) {
    gl::GLenum glAttachmentType = GetGlAttachmentType(attachmentType);

    gl::glFramebufferTexture2D(bindType, glAttachmentType, gl::GL_TEXTURE_2D, tex->Id(), 0);
}

void FrameBuffer::Attach(RenderBufferObject* rbo, FrameBufferAttachmentType attachmentType) {
    gl::GLenum glAttachmentType = GetGlAttachmentType(attachmentType);

    gl::glFramebufferRenderbuffer(bindType, glAttachmentType, gl::GL_RENDERBUFFER, rbo->Id());
}

void FrameBuffer::Bind() {
    glBindFramebuffer(bindType, id);
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(bindType, 0);
}

void FrameBuffer::Validate() {
    gl::GLenum status = gl::glCheckFramebufferStatus(bindType);

    switch(status) {
    case gl::GL_FRAMEBUFFER_COMPLETE:
        return;
        break;
    case gl::GL_FRAMEBUFFER_UNDEFINED:
        ASSERT_FAIL("Specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist")
        break;
    case gl::GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        ASSERT_FAIL("Some of the framebuffer attachment points are framebuffer incomplete")
        break;
    case gl::GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        ASSERT_FAIL("Framebuffer does not have at least one image attached to it")
        break;
    case gl::GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        ASSERT_FAIL("The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi")
        break;
    case gl::GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        ASSERT_FAIL("GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER")
        break;
    case gl::GL_FRAMEBUFFER_UNSUPPORTED:
        ASSERT_FAIL("Combination of internal formats of the attached images violates an implementation-dependent set of restrictions")
        break;
    case gl::GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        ASSERT_FAIL("The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES")
        break;
    case gl::GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        ASSERT_FAIL(" Some framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target")
        break;
    default:
        ASSERT_FAIL("Unknown framebuffer error")
        break;
    }
}

gl::GLenum FrameBuffer::GetGlAttachmentType(FrameBufferAttachmentType attachmentType) {
    gl::GLenum glAttachmentType;

    switch (attachmentType)
    {
    case FrameBufferAttachmentType::COLOR:
        glAttachmentType = gl::GL_COLOR_ATTACHMENT0;
        break;
    case FrameBufferAttachmentType::DEPTH:
        glAttachmentType = gl::GL_DEPTH_ATTACHMENT;
        break;
    case FrameBufferAttachmentType::STENCIL:
        glAttachmentType = gl::GL_STENCIL_ATTACHMENT;
        break;
    case FrameBufferAttachmentType::DEPTH_STENCIL:
        glAttachmentType = gl::GL_DEPTH_STENCIL_ATTACHMENT;
        break;    
    default:
        ASSERT_FAIL("Unknown frame buffer attachment type")
        break;
    }

    return glAttachmentType;
}