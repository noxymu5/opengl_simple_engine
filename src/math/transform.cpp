#include "transform.h"

#include <glm/gtx/quaternion.hpp>
#include "core/logging.h"

Transform::Transform() {
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

void Transform::SetRotationX(float angle) {
    matrix[1][1] = glm::cos(angle);
    matrix[1][2] = glm::sin(angle);
    matrix[2][1] = -glm::sin(angle);
    matrix[2][2] = glm::cos(angle);
}

void Transform::SetEulerAngles(glm::vec3 angles) {
    angles.x = glm::radians(angles.x);
    angles.y = glm::radians(angles.y);
    angles.z = glm::radians(angles.z);

    glm::quat quat(angles);
    glm::mat3 res = glm::toMat4(quat);
    
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            matrix[i][j] = res[i][j];
        }
    }
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