#ifndef util_vector_hpp
#define util_vector_hpp

#include <cmath>

#include <raylib.h>

namespace Util
{
    Vector2 scale(Vector2 vector, float factor);

    bool isZero(Vector2 vector);
}

#endif