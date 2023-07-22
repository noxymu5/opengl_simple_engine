#include "render_buffer_object.h"

#include <GLEW/glew.h>

RenderBufferObject::RenderBufferObject(unsigned int width, unsigned int height) {
    glGenRenderbuffers(1, &id);

    Bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    UnBind();
}

RenderBufferObject::~RenderBufferObject() {
    glDeleteRenderbuffers(1, &id);
}

void RenderBufferObject::Bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void RenderBufferObject::UnBind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}