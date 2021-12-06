#include "map.hpp"

namespace MapHandler
{
    RenderTexture2D mapFrameBuffer;
    Camera2D camera;

    void initializeMap(const char *filePath, float x, float y)
    {
        renderTmxMapToFramebuf(filePath, &mapFrameBuffer);

        camera.target = (Vector2){x, y};
        camera.offset = (Vector2){0, 0};
        camera.rotation = 0.0;
        camera.zoom = 1.0;
    }

    void updateMapView(float x, float y)
    {
        camera.target = (Vector2){x, y};
    }

    void drawMapView()
    {
        BeginMode2D(camera);
        DrawTextureRec(
            mapFrameBuffer.texture,
            (Rectangle){0, 0, (float)mapFrameBuffer.texture.width, (float)-mapFrameBuffer.texture.height},
            (Vector2){0.0, 0.0},
            WHITE);
        EndMode2D();
    }

    void renderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf)
    {
        tmx_layer *layer = NULL;

        // Setting these two function pointers allows TMX lib to load the tileset graphics and
        // set each tile's resource_image property properly.
        tmx_img_load_func = (void *(*)(const char *))loadMapTexture;
        tmx_img_free_func = (void (*)(void *))unloadMapTexture;
        tmx_map *mapTmx = tmx_load(mapFileName);
        if (mapTmx == NULL)
        {
            tmx_perror("tmx_load");
            return;
        }

        // Create a frame buffer
        // TODO: I don't life loading the RenderTexture here and unloading it in main(), but map info is needed to
        // allocate the buffer of the right size, so either load it here, or separate tmx_load part of the code into
        // a separate function to allow the application code to call LoadRenderTexture between tmx_load and actual
        // drawing of the map.
        *buf = LoadRenderTexture(mapTmx->width * mapTmx->tile_width, mapTmx->height * mapTmx->tile_height);

        BeginTextureMode(*buf); // start rendering into the buffer
        ClearBackground(SKYBLUE);
        // Iterate through TMX layers rendering them into buf
        layer = mapTmx->ly_head;
        while (layer)
        {
            if (layer->visible)
            {
                switch (layer->type)
                {
                case L_LAYER:
                {
                    TraceLog(LOG_INFO, "Render TMX layer \"%s\"", layer->name);
                    drawTmxLayer(mapTmx, layer);
                }
                break;

                // Group, Object and Image layer types are not implemented in this example
                case L_GROUP: // deliberate fall-through
                case L_OBJGR:
                {
                    TraceLog(LOG_INFO, "Parse TMX Objectgroup \"%s\"", layer->name);
                    parseTmxObjectgroup(mapTmx, layer);
                }
                case L_IMAGE:
                case L_NONE:
                default:
                    break;
                }
            }
            layer = layer->next;
        }
        EndTextureMode(); // stop rendering into the buffer

        tmx_map_free(mapTmx);
    }

    void parseTmxObjectgroup(tmx_map *map, tmx_layer *group)
    {
        tmx_object *head = group->content.objgr->head;

        while (head)
        {
            if (head->visible)
            {
                Rectangle dest = (Rectangle){
                    (float)head->x,
                    (float)head->y,
                    (float)head->width,
                    (float)head->height};

                switch (head->obj_type)
                {
                case OT_SQUARE:
                {
                    DrawRectangleLinesEx(dest, 2.5, RAYWHITE);
                    break;
                }
                case OT_POLYGON:
                case OT_POLYLINE:
                case OT_ELLIPSE:
                case OT_TILE:
                case OT_TEXT:
                case OT_POINT:
                default:
                    break;
                }

                head = head->next;
            }
        }
    }

    void drawTmxLayer(tmx_map *map, tmx_layer *layer)
    {
        unsigned long row, col;
        unsigned int gid;
        unsigned int flip;
        tmx_tile *tile;
        unsigned int tile_width;
        unsigned int tile_height;
        Rectangle sourceRect;
        Rectangle destRect;
        Texture2D *tsTexture; // tileset texture
        float rotation = 0.0;
        Vector2 origin = {0.0, 0.0};

        for (row = 0; row < map->height; row++)
        {
            for (col = 0; col < map->width; col++)
            {
                gid = layer->content.gids[(row * map->width) + col];
                flip = gid & ~TMX_FLIP_BITS_REMOVAL; // get flip operations from GID
                gid = gid & TMX_FLIP_BITS_REMOVAL;   // remove flip operations from GID to get tile ID
                tile = map->tiles[gid];
                if (tile != NULL)
                {
                    // Get tile's texture out of the tileset texture
                    if (tile->image != NULL)
                    {
                        tsTexture = (Texture2D *)tile->image->resource_image;
                        tile_width = tile->image->width;
                        tile_height = tile->image->height;
                    }
                    else
                    {
                        tsTexture = (Texture2D *)tile->tileset->image->resource_image;
                        tile_width = tile->tileset->tile_width;
                        tile_height = tile->tileset->tile_height;
                    }

                    sourceRect.x = tile->ul_x;
                    sourceRect.y = tile->ul_y;
                    sourceRect.width = destRect.width = tile_width;
                    sourceRect.height = destRect.height = tile_height;
                    destRect.x = col * tile_width;
                    destRect.y = row * tile_height;

                    // Deal with flips
                    origin.x = 0.0;
                    origin.y = 0.0;
                    rotation = 0.0;
                    switch (flip)
                    {
                    case TMX_FLIPPED_DIAGONALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                        rotation = 90.0;
                    }
                    break;
                    case TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                    }
                    break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = -90.0;
                    }
                    break;
                    case TMX_FLIPPED_HORIZONTALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                    }
                    break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY:
                    {
                        rotation = 90.0;
                    }
                    break;
                    case TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = 180.0;
                    }
                    break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                        rotation = 90.0;
                    }
                    break;
                    default:
                    {
                        origin.x = 0.0;
                        origin.y = 0.0;
                        rotation = 0.0;
                    }
                    break;
                    }

                    // Adjust origin to rotate around the center of the tile,
                    // which means destination recangle's origin must be adjusted.
                    if (rotation != 0.0)
                    {
                        origin.x = tile_width / 2;
                        origin.y = tile_height / 2;
                        destRect.x += tile_width / 2;
                        destRect.y += tile_height / 2;
                    }

                    // TODO: Take layer opacity into account
                    DrawTexturePro(*tsTexture, sourceRect, destRect, origin, rotation, WHITE);
                }
            }
        }
    }

    Texture2D *loadMapTexture(const char *fileName)
    {
        Texture2D *tex = (Texture2D *)malloc(sizeof(Texture2D));
        if (tex != NULL)
        {
            *tex = LoadTexture(fileName);
            TraceLog(LOG_INFO, "TMX texture loaded from %s", fileName);
            return tex;
        }
        return NULL;
    }

    void unloadMapTexture(Texture2D *tex)
    {
        if (tex != NULL)
        {
            UnloadTexture(*tex);
            free(tex);
        }
    }
}