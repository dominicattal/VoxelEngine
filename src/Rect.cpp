#include "Rect.h"
#include <iostream>

Rect::Rect(const char* image_path, Shader shader)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
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

    /*
    float vertices[] = {
         1.0f,  1.0f, 1.0f,  0.0f,
         1.0f, -1.0f, 1.0f,  1.0f,
        -1.0f, -1.0f, 0.0f,  1.0f,
        -1.0f,  1.0f, 0.0f,  0.0f
    };
    */

    float vertices[] = {
         0.5f,  0.5f, 1.0f,  0.0f,
         0.5f, -0.5f, 1.0f,  1.0f,
        -0.5f, -0.5f, 0.0f,  1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindTexture(GL_TEXTURE_2D, texture);

    const float mat[] = {
        0.707, -0.707, 0, 0,
        0.707, 0.707f, 0, 0,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f
    };
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat);
}

void Rect::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}