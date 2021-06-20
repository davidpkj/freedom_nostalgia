#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>

#include <raylib.h>

#include "util/vector.hpp"
#include "classes/character.hpp"

const int screenWidth = 800;
const int screenHeight = 450;
const unsigned int microsecond = 1000000;

Character character;
Texture2D texture;

void Initialize(void);
void Update(void);
void Draw(void);

int main(void)
{
    Initialize();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}

void Initialize() {
    InitWindow(screenWidth, screenHeight, "Dong");
    SetTargetFPS(144);

    character = {{0, 0}, {0, 0}, {(float)screenWidth / 2, (float)screenHeight / 2}, {30.0f, 70.0f}, 100.0f};
    texture = LoadTexture("../resources/tile.png");
}

void Update()
{
    float deltaTime = GetFrameTime();

    character.updateMovement(deltaTime);
}

void Draw()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);
    DrawTexture(texture, 0, 0, GREEN);
    DrawTexture(texture, 128, 0, GREEN);
    DrawRectangleV(character.position, character.size, RAYWHITE);

    EndDrawing();
}