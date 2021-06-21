#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>

#include <raylib.h>

#include "util/vector.hpp"
#include "classes/player.hpp"
#include "handlers/control.hpp"

const int screenWidth = 800;
const int screenHeight = 450;
const unsigned int microsecond = 1000000;

Player player = {{0, 0}, {(float)screenWidth / 2, (float)screenHeight / 2}, {30.0f, 70.0f}, 100.0f, "../resources/player.png"};
Texture2D playerTexture;
Texture2D texture;

void Deinitialize(void);
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

    Deinitialize();

    return 0;
}

void Deinitialize()
{
    UnloadTexture(playerTexture);
    UnloadTexture(texture);
    CloseWindow();
}

void Initialize()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Freedom Nostalgia");
    SetTargetFPS(144);

    playerTexture = LoadTexture("../resources/player.png");
    texture = LoadTexture("../resources/tile_grass.png");  // TODO: Manage textures in seperate manager
}

void Update()
{
    float deltaTime = GetFrameTime();

    control::update();
    player.updateMovement(deltaTime);
}

void Draw()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);
    DrawTexture(texture, 0, 0, GREEN);
    DrawTexture(texture, 128, 0, GREEN);  // TODO: Group into map handler
    player.draw(playerTexture);

    EndDrawing();
}