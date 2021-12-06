#include "texture.hpp"

namespace TextureHandler
{
    void loadTexture(fs::path texturePath)
    {
        std::string textureString = texturePath.string();
        const char *texture = textureString.c_str();

        // std::cout << texture << std::endl;
        Log::log(textureString);
        Log::log("yay");

        LoadTexture(texture);
    }

    void unloadTexture()
    {
    }

    void initialize()
    {
        fs::path path = ("../resources/textures");
        fs::directory_iterator end_iter;

        if (fs::exists(path) && fs::is_directory(path))
        {
            for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr)
            {
                try
                {
                    if (fs::is_regular_file(dir_itr->status()))
                    {
                        loadTexture(dir_itr->path());
                    }
                }
                catch (const std::exception &ex)
                {
                    std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Texure Handler: path does not exist" << std::endl;
        }

        std::cout << "Texture Handler initialized" << std::endl;
    }
}