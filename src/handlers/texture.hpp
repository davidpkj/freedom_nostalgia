#ifndef handler_texture_hpp
#define handler_texture_hpp

#include <cmath>
#include <iostream>

#include <boost/filesystem.hpp>
#include <raylib.h>

#include "../util/log.hpp"

namespace fs = boost::filesystem;

namespace TextureHandler
{
    void loadTexture();
    void unloadTexture();

    void initialize();
}

#endif