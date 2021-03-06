#include "player.hpp"

Player::Player(Vector2 direction, Vector2 position, Vector2 size, float speed, const char *texture) : Character(direction, position, size, speed, texture)
{
    this->playerDestinationRectangle = {this->position.x, this->position.y, 128.0f, 128.0f};
    this->playerSourceRectangle = {0.0f, 0.0f, 128.0f, 128.0f};

    std::cout << "Player initialized" << std::endl;
}

void Player::updateMovement(float deltaTime)
{
    if (Control::up > 0.0f)
    {
        this->position.y -= this->speed * deltaTime * Control::up;
    }
    if (Control::down > 0.0f)
    {
        this->position.y += this->speed * deltaTime * Control::down;
    }
    if (Control::left > 0.0f)
    {
        this->position.x -= this->speed * deltaTime * Control::left;
    }
    if (Control::right > 0.0f)
    {
        this->position.x += this->speed * deltaTime * Control::right;
    }

    this->playerDestinationRectangle.x = this->position.x;
    this->playerDestinationRectangle.y = this->position.y;
};

void Player::draw(Texture2D playerTexture)
{
    DrawTexturePro(playerTexture, playerSourceRectangle, playerDestinationRectangle, {0, 0}, 0, RAYWHITE);
}
