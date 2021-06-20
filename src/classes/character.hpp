#ifndef class_character_hpp
#define class_character_hpp

#include <cmath>

#include <raylib.h>

class Character
{
public:
    Vector2 initialDirection;
    Vector2 direction;
    Vector2 position;
    Vector2 size;
    float speed;

    void updateMovement(float deltaTime);
};

#endif