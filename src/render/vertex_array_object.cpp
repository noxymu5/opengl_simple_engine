#include "vertex_array_object.h"

#include <GLEW/glew.h>

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

void VertexArrayObject::Bind() {
    glBindVertexArray(id);
}

void VertexArrayObject::UnBind() {
    glBindVertexArray(0);
}