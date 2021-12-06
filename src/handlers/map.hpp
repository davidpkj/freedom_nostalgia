#ifndef handler_map_hpp
#define handler_map_hpp

#include <raylib.h>
#include <tmx.h>

#include "../classes/player.hpp"

namespace MapHandler
{
    void initializeMap(const char *filePath, float x, float y);
    void updateMapView(float x, float y);
    void drawMapView();

    void renderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
    void parseTmxObjectgroup(tmx_map *map, tmx_layer *layer);
    void drawTmxLayer(tmx_map *map, tmx_layer *layer);

    Texture2D *loadMapTexture(const char *fileName);
    void unloadMapTexture(Texture2D *tex);
}

#endif