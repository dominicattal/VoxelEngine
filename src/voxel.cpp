#include "voxel.h"
#include <iostream>
#include <cmath>
#define PI 3.141592659

Voxel::Voxel(const char* image_path, Shader* shader_, vec3f position_, std::unordered_map<vec3f, Voxel*>* voxels_)
{
    shader = shader_;
    position = position_;
    voxels = voxels_;

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

    float left[] = {
        -0.5, -0.5,  0.5,  0.0,  0.0,
         0.5, -0.5,  0.5,  1.0,  0.0,
         0.5,  0.5,  0.5,  1.0,  1.0,  
        -0.5,  0.5,  0.5,  0.0,  1.0
    };
    float right[] = {
         0.5,  0.5, -0.5,  1.0,  1.0,  
         0.5, -0.5, -0.5,  1.0,  0.0,
        -0.5, -0.5, -0.5,  0.0,  0.0,
        -0.5,  0.5, -0.5,  0.0,  1.0  
    };
    float front[] = {
        -0.5,  0.5,  0.5,  1.0,  0.0,
        -0.5,  0.5, -0.5,  1.0,  1.0,
        -0.5, -0.5, -0.5,  0.0,  1.0,
        -0.5, -0.5,  0.5,  0.0,  0.0
    };
    float back[] = {
         0.5, -0.5, -0.5,  0.0,  0.0,
         0.5,  0.5, -0.5,  1.0,  0.0,
         0.5,  0.5,  0.5,  1.0,  1.0,
         0.5, -0.5,  0.5,  0.0,  1.0
    };
    float top[] = {
         0.5,  0.5,  0.5,  1.0,  1.0,
         0.5,  0.5, -0.5,  1.0,  0.0,
        -0.5,  0.5, -0.5,  0.0,  0.0,
        -0.5,  0.5,  0.5,  0.0,  1.0, 
    };
    float bottom[] = {
        -0.5, -0.5, -0.5,  0.0,  0.0,
         0.5, -0.5, -0.5,  1.0,  0.0,
         0.5, -0.5,  0.5,  1.0,  1.0,
        -0.5, -0.5,  0.5,  0.0,  1.0, 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    float* render_order[] = {
        left, right,
        front, back,
        top, bottom
    };
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenBuffers(1, &EBO);

    for (int i = 0; i < 6; i++)
    {
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, 80, render_order[i], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    glBindTexture(GL_TEXTURE_2D, texture);
}

void Voxel::draw()
{
    float x = position.x, y = position.y, z = position.z;
    const float model[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };
    shader->use();
    unsigned int modelID = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelID, 1, GL_FALSE, model);
    for (int i = 0; i < 6; i++)
    {
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}