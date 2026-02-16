//
// Created by jakub on 16.02.2026.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

enum class TextureType {
    DIFFUSE,
    SPECULAR
};

class Texture {
public:
    unsigned int ID;
    TextureType type;   // texture_diffuse (normal texture), texture_specular (for lighting)
    std::string path;

    Texture(const char *path, TextureType type);
    void bind(int unit) const;
    void unbind();

private:
    void loadTexture(const char *path);
};



#endif //TEXTURE_H
