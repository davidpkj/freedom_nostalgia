#ifndef class_character_hpp
#define class_character_hpp

#include <iostream>
#include <cmath>

#include <raylib.h>

class Character
{
public:
    Vector2 direction;
    Vector2 position;
    Vector2 size;
    float speed;
    const char *texture;

    Character(Vector2 direction, Vector2 position, Vector2 size, float speed, const char *texture);
};

#endif