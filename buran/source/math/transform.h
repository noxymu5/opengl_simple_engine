#pragma once

#include "core/glm_declarations.h"

class Transform
{
private:
    glm::mat4 matrix{1};
public:
    Transform();
    ~Transform();

    glm::mat4 Get() { return matrix; }

    glm::vec3 Up();
    glm::vec3 Right();
    glm::vec3 Forward();

    void Translate(glm::vec3 translation);
    void Rotate(float angleRad, glm::vec3 axis);
    void Scale(glm::vec3 scale);

    void RotateY(float angle);
    void RotateZ(float angle);
    void RotateX(float angle);
    void SetRotationX(float angle);

    void SetEulerAngles(glm::vec3 angles);

    void SetPosition(glm::vec3 position);
    void SetMatrix(glm::mat4 matr);

    glm::vec3 GetPosition();
};