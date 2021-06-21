#include "control.hpp"

namespace control
{
    void update()
    {
        int id = 2;

        float FirstAxis = GetGamepadAxisMovement(id, 0);
        float SecondAxis = GetGamepadAxisMovement(id, 1);

        if (0.0f >= SecondAxis && SecondAxis >= -1.0f)
        {
            up = SecondAxis * -1;
        }
        if (0.0f <= SecondAxis && SecondAxis <= 1.0f)
        {
            down = SecondAxis;
        }
        if (0.0f >= FirstAxis && FirstAxis >= -1.0f)
        {
            left = FirstAxis * -1;
        }
        if (0.0f <= FirstAxis && FirstAxis <= 1.0f)
        {
            right = FirstAxis;
        }

        if (IsKeyDown(KEY_UP))
        {
            up = 1.0f;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            down = 1.0f;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            left = 1.0f;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            right = 1.0f;
        }
    }
}