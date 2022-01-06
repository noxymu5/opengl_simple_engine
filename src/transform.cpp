#include "transform.h"

Transform::Transform() {
    matrix = glm::mat4(1.0);
}

Transform::~Transform() {
}

void Transform::Translate(glm::vec3 translation) {
    matrix = glm::translate(glm::mat4(1.0f), translation) * matrix;
}

void Transform::Rotate(float angleRad, glm::vec3 axis) {
    matrix = matrix * glm::rotate(glm::mat4(1.0f), angleRad, axis);
}

void Transform::Scale(glm::vec3 scale) {
    matrix = glm::scale(matrix, scale);
}

void Transform::SetPosition(glm::vec3 position) {
    matrix[3][0] = position[0];
    matrix[3][1] = position[1];
    matrix[3][2] = position[2];
}

glm::vec3 Transform::GetPosition() {
    return glm::vec3(matrix[3]);
}