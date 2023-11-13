#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture
{
    unsigned int ID;
    Texture(const char* image_path);
    void use();
};

#endif /* TEXTURE_H */