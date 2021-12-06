#include "character.hpp"

Character::Character(Vector2 direction, Vector2 position, Vector2 size, float speed, const char *texture)
{
    this->direction = direction;
    this->position = position;
    this->size = size;
    this->speed = speed;
    this->texture = texture;

    std::cout << "Character initialized" << std::endl;
}