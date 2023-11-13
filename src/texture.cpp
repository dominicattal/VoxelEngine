#include <glad.h>
#include <stb_image.h>
#include <iostream>
#include "texture.h"

Texture::Texture(const char* image_path)
{
    glGenTextures(1, &ID);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(image_path, &width, &height, &nrChannels, 0); 
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}