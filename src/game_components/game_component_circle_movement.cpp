#include "game_component_circle_movement.h"

#include <glm/vec3.hpp>
#include <math.h>

#include "serializers/game_component_serializer.h"

BEGIN_SERIALIZER(GameComponentCircleMovement)
EXPOTR_FIELD(rotationSpeed, float)
EXPOTR_FIELD(height, float)
EXPOTR_FIELD(radius, float)
END_SERIALIZER(GameComponentCircleMovement)

void GameComponentCircleMovement::Update(float dt) {
    angle += rotationSpeed * dt;

    glm::vec3 position(sin(angle) * radius, height, cos(angle) * radius);
    owner->SetPos(position);
}