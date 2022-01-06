#ifndef TRANSFORM
#define TRANSFORM

#include "common.h"

class Transform
{
private:
    glm::mat4 matrix;
public:
    Transform();
    ~Transform();

    glm::mat4 Get() { return matrix; }

    void Translate(glm::vec3 translation);
    void Rotate(float angleRad, glm::vec3 axis);
    void Scale(glm::vec3 scale);

    void SetPosition(glm::vec3 position);
    glm::vec3 GetPosition();
};

#endif