#include "render.h"

void bindVAO(unsigned int ID)
{
    glBindVertexArray(ID);
}

void bindVBO(unsigned int ID)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void bindVBOData(int size, const float* data)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void bindTexture(unsigned int ID)
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void bindTextureData(const char* image_path)
{
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

void drawTriangles(int vertex_count)
{
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}