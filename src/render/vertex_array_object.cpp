#include "vertex_array_object.h"

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