#include "voxel.h"

unsigned int VAOs[6], VBOs[6], EBO, modelID;
std::unordered_map<vec3f, Voxel*>* voxels = new std::unordered_map<vec3f, Voxel*>();
std::unordered_map<vec3f, Voxel*>* left   = new std::unordered_map<vec3f, Voxel*>();
std::unordered_map<vec3f, Voxel*>* right  = new std::unordered_map<vec3f, Voxel*>();
std::unordered_map<vec3f, Voxel*>* front  = new std::unordered_map<vec3f, Voxel*>();
std::unordered_map<vec3f, Voxel*>* back   = new std::unordered_map<vec3f, Voxel*>();
std::unordered_map<vec3f, Voxel*>* top    = new std::unordered_map<vec3f, Voxel*>();
std::unordered_map<vec3f, Voxel*>* bottom = new std::unordered_map<vec3f, Voxel*>();

vec3f dirs[] = {
    vec3f(0, 0,  1),
    vec3f(0, 0, -1),
    vec3f(-1, 0, 0),
    vec3f( 1, 0, 0),
    vec3f(0,  1, 0),
    vec3f(0, -1, 0)
};

Voxel::Voxel()
{

}

void initalizeVoxels()
{
    float left[] = {
        0.0f, 0.0f, 1.0f, 0.0, 0.0,
        1.0f, 0.0f, 1.0f, 1.0, 0.0,
        1.0f, 1.0f, 1.0f, 1.0, 1.0,  
        0.0f, 1.0f, 1.0f, 0.0, 1.0
    };
    float right[] = {
        1.0f, 1.0f, 0.0f, 1.0, 1.0,  
        1.0f, 0.0f, 0.0f, 1.0, 0.0,
        0.0f, 0.0f, 0.0f, 0.0, 0.0,
        0.0f, 1.0f, 0.0f, 0.0, 1.0  
    };
    float front[] = {
        0.0f, 1.0f, 1.0f, 1.0, 0.0,
        0.0f, 1.0f, 0.0f, 1.0, 1.0,
        0.0f, 0.0f, 0.0f, 0.0, 1.0,
        0.0f, 0.0f, 1.0f, 0.0, 0.0
    };
    float back[] = {
         1.0f, 0.0f, 0.0f, 0.0, 0.0,
         1.0f, 1.0f, 0.0f, 1.0, 0.0,
         1.0f, 1.0f, 1.0f, 1.0, 1.0,
         1.0f, 0.0f, 1.0f, 0.0, 1.0
    };
    float top[] = {
        1.0f,  1.0f, 1.0f, 1.0, 1.0,
        1.0f,  1.0f, 0.0f, 1.0, 0.0,
        0.0f,  1.0f, 0.0f, 0.0, 0.0,
        0.0f,  1.0f, 1.0f, 0.0, 1.0, 
    };
    float bottom[] = {
        0.0f, 0.0f, 0.0f, 0.0, 0.0,
        1.0f, 0.0f, 0.0f, 1.0, 0.0,
        1.0f, 0.0f, 1.0f, 1.0, 1.0,
        0.0f, 0.0f, 1.0f, 0.0, 1.0, 
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

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 100; k++)
            {
                createVoxel(vec3f(i, -j-1, k));
            }
        }
    }
}

void linkVoxelShader(Shader shader)
{
    modelID = glGetUniformLocation(shader.ID, "model");
}

void updateVoxels(vec3f position)
{
    vec3f pos_left   = position + dirs[0];
    vec3f pos_right  = position + dirs[1];
    vec3f pos_front  = position + dirs[2];
    vec3f pos_back   = position + dirs[3];
    vec3f pos_top    = position + dirs[4];
    vec3f pos_bottom = position + dirs[5];

    if (voxels->count(position) == 0)
    {
        if (voxels->count(pos_left) == 0)
        {
        }
    }
    else
    {
        Voxel* voxel = voxels->at(position);
        if (voxels->count(pos_left) == 0)
        {
            left->insert({position, voxel});
        }
        else
        {
            right->erase(pos_left);
        }
        if (voxels->count(pos_right) == 0)
        {
            right->insert({position, voxel});
        }
        else
        {
            left->erase(pos_right);
        }

        if (voxels->count(pos_front) == 0)
        {
            front->insert({position, voxel});
        }
        else
        {
            back->erase(pos_front);
        }
        if (voxels->count(pos_back) == 0)
        {
            back->insert({position, voxel});
        }
        else
        {
            front->erase(pos_back);
        }

        if (voxels->count(pos_top) == 0)
        {
            top->insert({position, voxel});
        }
        else
        {
            bottom->erase(pos_top);
        }
        if (voxels->count(pos_bottom) == 0)
        {
            bottom->insert({position, voxel});
        }
        else
        {
            top->erase(pos_bottom);
        }
    }
}

void createVoxel(vec3f position)
{
    voxels->insert({position, new Voxel()});
    updateVoxels(position);
}

void drawFace(vec3f position)
{
    float x = position.x, y = position.y, z = position.z;
    const float model[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };
    glUniformMatrix4fv(modelID, 1, GL_FALSE, model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawVoxels()
{
    drawLeftFaces();
    drawRightFaces();
    drawFrontFaces();
    drawBackFaces();
    drawTopFaces();
    drawBottomFaces();
}

void drawLeftFaces()
{
    glBindVertexArray(VAOs[0]);
    for (auto pair : *left)
    {
        drawFace(pair.first);
    }
}

void drawRightFaces()
{
    glBindVertexArray(VAOs[1]);
    for (auto pair : *right)
    {
        drawFace(pair.first);
    }
}

void drawFrontFaces()
{
    glBindVertexArray(VAOs[2]);
    for (auto pair : *front)
    {
        drawFace(pair.first);
    }
}

void drawBackFaces()
{
    glBindVertexArray(VAOs[3]);
    for (auto pair : *back)
    {
        drawFace(pair.first);
    }
}

void drawTopFaces()
{
    glBindVertexArray(VAOs[4]);
    for (auto pair : *top)
    {
        drawFace(pair.first);
    }
}

void drawBottomFaces()
{
    glBindVertexArray(VAOs[5]);
    for (auto pair : *bottom)
    {
        drawFace(pair.first);
    }
}