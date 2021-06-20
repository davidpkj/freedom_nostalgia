#include "vector.hpp"

namespace util
{
    RAYLIB_H::Vector2 scale(RAYLIB_H::Vector2 vector, float factor)
    {
        return {vector.x * factor, vector.y * factor};
    }

    bool isZero(Vector2 vector)
    {
        float result = sqrt(vector.x * vector.x + vector.y * vector.y);

        if (result == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}