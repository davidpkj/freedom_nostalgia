#include "vector.hpp"

namespace Util
{
    Vector2 scale(Vector2 vector, float factor)
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