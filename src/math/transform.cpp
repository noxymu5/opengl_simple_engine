#include "transform.h"

Transform::Transform() {
    for(int idx = 0; idx < 4; ++idx){
        matrix[idx][idx] = 1;
    }
}

Transform::~Transform() {
}

glm::vec3 Transform::Up() {
    return glm::vec3(matrix[1]);
}

glm::vec3 Transform::Right() {
    return glm::vec3(matrix[0]);
}

glm::vec3 Transform::Forward() {
    return glm::vec3(matrix[2]);
}

void Transform::Translate(glm::vec3 translation) {
    matrix = glm::translate(glm::mat4(1.0f), translation) * matrix;
}

void Transform::Rotate(float angleRad, glm::vec3 axis) {
    matrix = glm::rotate(glm::mat4(1.0f), angleRad, axis) * matrix;
}

void Transform::Scale(glm::vec3 scale) {
    matrix = glm::scale(matrix, scale);
}

void Transform::RotateY(float angle) {
    glm::mat4 rot(0);
    for(int idx = 0; idx < 4; ++idx){
        rot[idx][idx] = 1;
    }

    rot[0][0] = glm::cos(angle);
    rot[0][2] = glm::sin(angle);
    rot[2][0] = -glm::sin(angle);
    rot[2][2] = glm::cos(angle);
    matrix = matrix * rot;
}

void Transform::RotateZ(float angle) {
    glm::mat4 rot(0);
    for(int idx = 0; idx < 4; ++idx){
        rot[idx][idx] = 1;
    }

    rot[0][0] = glm::cos(angle);
    rot[0][1] = glm::sin(angle);
    rot[1][0] = -glm::sin(angle);
    rot[1][1] = glm::cos(angle);

    matrix = matrix * rot;
}

void Transform::RotateX(float angle) {
    glm::mat4 rot(0);
    for(int idx = 0; idx < 4; ++idx){
        rot[idx][idx] = 1;
    }

    rot[1][1] = glm::cos(angle);
    rot[1][2] = glm::sin(angle);
    rot[2][1] = -glm::sin(angle);
    rot[2][2] = glm::cos(angle);

    matrix = matrix * rot;
}

void Transform::SetPosition(glm::vec3 position) {
    matrix[3][0] = position[0];
    matrix[3][1] = position[1];
    matrix[3][2] = position[2];
}

void Transform::SetMatrix(glm::mat4 matr) {
    matrix = matr;
}

glm::vec3 Transform::GetPosition() {
    return glm::vec3(matrix[3]);
}