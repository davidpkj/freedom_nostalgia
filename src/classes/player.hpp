#ifndef class_player_hpp
#define class_player_hpp

#include <cmath>

#include <raylib.h>

#include "character.hpp"
#include "../handlers/control.hpp"

class Player : public Character
{
protected:
    Rectangle playerDestinationRectangle;
    Rectangle playerSourceRectangle;

public:
    void updateMovement(float deltaTime);
    void draw(Texture2D playerTexture);

    Player(Vector2 direction, Vector2 position, Vector2 size, float speed, const char *texture);
};

#endif