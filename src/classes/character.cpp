#include "character.hpp"

void Character::updateMovement(float deltaTime)
{
    if (IsKeyDown(KEY_RIGHT))
        position.x += speed * deltaTime;
    if (IsKeyDown(KEY_LEFT))
        position.x -= speed * deltaTime;
    if (IsKeyDown(KEY_UP))
        position.y -= speed * deltaTime;
    if (IsKeyDown(KEY_DOWN))
        position.y += speed * deltaTime;
};
