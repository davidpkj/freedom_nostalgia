#ifndef util_vector_hpp
#define util_vector_hpp

#include <cmath>

#include <raylib.h>

namespace util
{
    RAYLIB_H::Vector2 scale(RAYLIB_H::Vector2 vector, float factor);

    bool isZero(Vector2 vector);
}

#endif