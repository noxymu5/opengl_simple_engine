#include "camera.h"

#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::GetViewMatrix() {
    glm::vec3 up = transform.Up();
    glm::vec3 forward = transform.Forward();
    glm::vec3 right = transform.Right();

    return glm::lookAt(transform.GetPosition(), transform.GetPosition() + forward, up);
}