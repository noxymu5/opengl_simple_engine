#include "vertex_array_object.h"

#include <glbinding/gl/gl.h>

VertexArrayObject::VertexArrayObject() {
    gl::glGenVertexArrays(1, &id);
    gl::glBindVertexArray(id);
}

void VertexArrayObject::Bind() {
    gl::glBindVertexArray(id);
}

void VertexArrayObject::UnBind() {
    gl::glBindVertexArray(0);
}