#include "render_buffer_object.h"

#include <glbinding/gl/gl.h>

RenderBufferObject::RenderBufferObject(unsigned int width, unsigned int height) {
    gl::glGenRenderbuffers(1, &id);

    Bind();
    gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH24_STENCIL8, width, height);
    UnBind();
}

RenderBufferObject::~RenderBufferObject() {
    gl::glDeleteRenderbuffers(1, &id);
}

void RenderBufferObject::Bind() {
    gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, id);
}

void RenderBufferObject::UnBind() {
    gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, 0);
}