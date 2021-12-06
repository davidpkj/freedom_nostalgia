#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>

#include <raylib.h>

#include "util/log.hpp"
#include "util/vector.hpp"
#include "classes/player.hpp"
#include "handlers/control.hpp"
#include "handlers/texture.hpp"
#include "handlers/map.hpp"

const int screenWidth = 800;
const int screenHeight = 450;
const unsigned int microsecond = 1000000;

Player player = {{0, 0}, {(float)screenWidth / 2, (float)screenHeight / 2}, {30.0f, 70.0f}, 100.0f, "../resources/player.png"};
Music music;

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
    UnloadMusicStream(music);
    CloseWindow();
}

void Initialize()
{
    Log::initialize();

    InitWindow(screenWidth, screenHeight, "Freedom Nostalgia");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetExitKey(KEY_NULL);
    SetTargetFPS(144);
    InitAudioDevice();

    music = LoadMusicStream("../resources/audio/background-half.mp3");
    TextureHandler::initialize();
    MapHandler::initializeMap("../resources/maps/world.tmx", player.position.x, player.position.y);

    PlayMusicStream(music);
}

void Update()
{
    float deltaTime = GetFrameTime();

    Control::update();
    UpdateMusicStream(music);
    player.updateMovement(deltaTime);
    MapHandler::updateMapView(player.position.x, player.position.y);
}

void Draw()
{
    BeginDrawing();

    MapHandler::drawMapView();

    EndDrawing();
}
