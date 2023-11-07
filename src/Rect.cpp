#include "Rect.h"
#include <iostream>
#include <cmath>
#define PI 3.141592659

Rect::Rect(const char* image_path, Shader* _shader)
{
    shader = _shader;
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
         0.5f,  0.5f, 0, 1.0f,  0.0f,
         0.5f, -0.5f, 0, 1.0f,  1.0f,
        -0.5f, -0.5f, 0, 0.0f,  1.0f,
        -0.5f,  0.5f, 0, 0.0f,  0.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindTexture(GL_TEXTURE_2D, texture);  
}

void Rect::draw()
{
    const float model[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 1
    };
    /*
    float a = 1; //aspect ratio width / height
    float fov = 45 * PI / 180; //vertical cam angle
    float nz = 0.1f; // near clipping
    float fz = 100.0f; //far clipping
    float v1, v2, v3, v4;
    v1 = 1 / (a * tan(fov / 2));
    v2 = 1 / (tan(fov / 2));
    v3 = (-nz - fz) / (nz - fz);
    v4 = (2 * fz * nz) / (nz - fz);
    const float pers[] = {
        v1, 0, 0, 0,
        0, v2, 0, 0,
        0, 0, v3, 1,
        0, 0, v4, 0
    };
    */
    
    shader->use();
    unsigned int modelID = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelID, 1, GL_FALSE, model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}