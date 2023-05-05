#include "buffers.h"

#include <GLEW/glew.h>

//Vertex buffer

VertexBuffer::VertexBuffer(const float* verticesData, const unsigned int size) {
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