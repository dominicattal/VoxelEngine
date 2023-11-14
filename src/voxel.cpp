#include "voxel.h"

/*
    float left[] = {
        0.0f, 0.0f, 1.0f, 0.0, 0.0,
        1.0f, 0.0f, 1.0f, 1.0, 0.0,
        0.0f, 1.0f, 1.0f, 0.0, 1.0,
        1.0f, 0.0f, 1.0f, 1.0, 0.0,
        1.0f, 1.0f, 1.0f, 1.0, 1.0,  
        0.0f, 1.0f, 1.0f, 0.0, 1.0
    };
    float right[] = {
        1.0f, 1.0f, 0.0f, 1.0, 1.0,  
        1.0f, 0.0f, 0.0f, 1.0, 0.0,
        0.0f, 1.0f, 0.0f, 0.0, 1.0,
        1.0f, 0.0f, 0.0f, 1.0, 0.0,
        0.0f, 0.0f, 0.0f, 0.0, 0.0,
        0.0f, 1.0f, 0.0f, 0.0, 1.0  
    };
    float front[] = {
        0.0f, 1.0f, 1.0f, 1.0, 0.0,
        0.0f, 1.0f, 0.0f, 1.0, 1.0,
        0.0f, 0.0f, 1.0f, 0.0, 0.0,
        0.0f, 1.0f, 0.0f, 1.0, 1.0,
        0.0f, 0.0f, 0.0f, 0.0, 1.0,
        0.0f, 0.0f, 1.0f, 0.0, 0.0
    };
    float back[] = {
         1.0f, 0.0f, 0.0f, 0.0, 0.0,
         1.0f, 1.0f, 0.0f, 1.0, 0.0,
         1.0f, 0.0f, 1.0f, 0.0, 1.0,
         1.0f, 1.0f, 0.0f, 1.0, 0.0,
         1.0f, 1.0f, 1.0f, 1.0, 1.0,
         1.0f, 0.0f, 1.0f, 0.0, 1.0
    };
    float top[] = {
        1.0f,  1.0f, 1.0f, 1.0, 1.0,
        1.0f,  1.0f, 0.0f, 1.0, 0.0,
        0.0f,  1.0f, 1.0f, 0.0, 1.0, 
        1.0f,  1.0f, 0.0f, 1.0, 0.0,
        0.0f,  1.0f, 0.0f, 0.0, 0.0,
        0.0f,  1.0f, 1.0f, 0.0, 1.0
    };
    float bottom[] = {
        0.0f, 0.0f, 0.0f, 0.0, 0.0,
        1.0f, 0.0f, 0.0f, 1.0, 0.0,
        0.0f, 0.0f, 1.0f, 0.0, 1.0,
        1.0f, 0.0f, 0.0f, 1.0, 0.0,
        1.0f, 0.0f, 1.0f, 1.0, 1.0,
        0.0f, 0.0f, 1.0f, 0.0, 1.0 
    };
*/

float* vertex_data;
unsigned int VAO, VBO;
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

int totalFaces()
{
    int size = 0;
    size += left->size();
    size += right->size();
    size += front->size();
    size += back->size();
    size += top->size();
    size += bottom->size();
    return size;
}

void initalizeVoxels()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

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
            left->insert({position, voxel});
        else
            right->erase(pos_left);

        if (voxels->count(pos_right) == 0)
            right->insert({position, voxel});
        else
            left->erase(pos_right);

        if (voxels->count(pos_front) == 0)
            front->insert({position, voxel});
        else
            back->erase(pos_front);

        if (voxels->count(pos_back) == 0)
            back->insert({position, voxel});
        else
            front->erase(pos_back);

        if (voxels->count(pos_top) == 0)
            top->insert({position, voxel});
        else
            bottom->erase(pos_top);

        if (voxels->count(pos_bottom) == 0)
            bottom->insert({position, voxel});
        else
            top->erase(pos_bottom);
    }

    updateVertexData();
}

void updateVertexData()
{
    delete[] vertex_data;
    int size = totalFaces();
    vertex_data = new float[size * 6 * 5];

    int i = 0;
    for (auto iter = left->begin(); iter != left->end(); iter++)
    {
        i++;
    }

    for (auto iter = right->begin(); iter != right->end(); iter++)
    {
        i++;
    }

    for (auto iter = top->begin(); iter != top->end(); iter++)
    {
        updateTopFaces(iter->first, i * 30);
        i++;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size * 6 * 5 * 4, vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void createVoxel(vec3f position)
{
    voxels->insert({position, new Voxel()});
    updateVoxels(position);
}

void drawVoxels()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, totalFaces() * 6);
}

void updateTopFaces(vec3f pos, int idx)
{
    vertex_data[idx]    = pos.x + 1;
    vertex_data[idx+1]  = pos.y + 1;
    vertex_data[idx+2]  = pos.z + 1;
    vertex_data[idx+3]  = 1.0;
    vertex_data[idx+4]  = 1.0;
    vertex_data[idx+5]  = pos.x + 1;
    vertex_data[idx+6]  = pos.y + 1;
    vertex_data[idx+7]  = pos.z;
    vertex_data[idx+8]  = 1.0;
    vertex_data[idx+9]  = 0.0;
    vertex_data[idx+10] = pos.x;
    vertex_data[idx+11] = pos.y + 1;
    vertex_data[idx+12] = pos.z + 1;
    vertex_data[idx+13] = 0.0;
    vertex_data[idx+14] = 1.0;
    vertex_data[idx+15] = pos.x + 1;
    vertex_data[idx+16] = pos.y + 1;
    vertex_data[idx+17] = pos.z;
    vertex_data[idx+18] = 1.0;
    vertex_data[idx+19] = 0.0;
    vertex_data[idx+20] = pos.x ;
    vertex_data[idx+21] = pos.y + 1;
    vertex_data[idx+22] = pos.z;
    vertex_data[idx+23] = 0.0;
    vertex_data[idx+24] = 0.0;
    vertex_data[idx+25] = pos.x;
    vertex_data[idx+26] = pos.y + 1;
    vertex_data[idx+27] = pos.z + 1;
    vertex_data[idx+28] = 0.0;
    vertex_data[idx+29] = 1.0;
}