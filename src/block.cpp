#include "block.h"
#include <iostream>

unsigned int VAO, VBO, TEX;
unsigned int num_faces;
float* vertex_data;
std::unordered_map<vec3f, Block*>* blocks;
std::unordered_map<Face, std::unordered_map<vec3f, blocktype>*> faces;
std::unordered_map<Face, float*> coords;

vec3f dirs[] = {
    vec3f(0, 0,  1),
    vec3f(0, 0, -1),
    vec3f(-1, 0, 0),
    vec3f( 1, 0, 0),
    vec3f(0,  1, 0),
    vec3f(0, -1, 0)
};

Face opposite_face[] = {
    RIGHT,
    LEFT,
    BACK,
    FRONT,
    BOTTOM,
    TOP
};

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

Block::Block(blocktype type_)
{
    type = type_;
}

void initalizeBlocks()
{
    num_faces = 0;
    vertex_data = new float[0];
    blocks = new std::unordered_map<vec3f, Block*>();

    for (int i = 0; i < 6; i++)
    {
        faces[static_cast<Face>(i)] = new std::unordered_map<vec3f, blocktype>();
    }

    coords[LEFT]   = left;
    coords[RIGHT]  = right;
    coords[FRONT]  = front;
    coords[BACK]   = back;
    coords[TOP]    = top;
    coords[BOTTOM] = bottom;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenTextures(1, &TEX);
    bindTexture(TEX);
    bindTextureData("assets/block_sheet.png");

    int l = 0;
    for (int i = 0; i < 1001; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 1001; k++)
            {
                if (l % 10000 == 0)
                {
                    std::cout << l << std::endl;
                }
                if (l % 2 == 0)
                    createBlock(TYPE2, vec3f(i, -j-1, k));
                else
                    createBlock(TYPE1, vec3f(i, -j-1, k));
                l++;
            }
        }
    }
    std::cout << num_faces << std::endl;
    updateVertexData();
}

void drawBlocks()
{
    bindVAO(VAO);
    drawTriangles(num_faces * 6);
}

void createBlock(blocktype type, vec3f position)
{
    blocks->insert({position, new Block(type)});
    updatePosition(position);
}

void updatePosition(vec3f position)
{
    if (blocks->count(position) > 0)
    {
        Block* block = blocks->at(position);
        for (int i = 0; i < 6; i++)
        {
            Face face = static_cast<Face>(i);
            vec3f other_pos = position + dirs[face];
            Face other_face = opposite_face[face];
            if (blocks->count(other_pos))
            {
                faces[other_face]->erase(other_pos);
                num_faces--;
            }
            else
            {
                faces[face]->insert({position, block->type});
                num_faces++;
            }
        }
    }
}

void updateVertexData()
{
    delete[] vertex_data;
    vertex_data = new float[num_faces * 6 * 5];
    int idx = 0;

    for (auto pair : faces)
    {
        Face face = pair.first;
        std::unordered_map<vec3f, blocktype>* data = pair.second;
        for (auto pair2 : *data)
        {
            vec3f pos = pair2.first;
            blocktype type = pair2.second;
            int t = static_cast<int>(type);
            float p = 1.0 / NUM_TYPES;
            vertex_data[idx]    = pos.x + coords[face][0];
            vertex_data[idx+1]  = pos.y + coords[face][1];
            vertex_data[idx+2]  = pos.z + coords[face][2];
            vertex_data[idx+3]  = p * t + p * coords[face][3];
            vertex_data[idx+4]  = p * t + p * coords[face][4];
            vertex_data[idx+5]  = pos.x + coords[face][5];
            vertex_data[idx+6]  = pos.y + coords[face][6];
            vertex_data[idx+7]  = pos.z + coords[face][7];
            vertex_data[idx+8]  = p * t + p * coords[face][8];
            vertex_data[idx+9]  = p * t + p * coords[face][9];
            vertex_data[idx+10] = pos.x + coords[face][10];
            vertex_data[idx+11] = pos.y + coords[face][11];
            vertex_data[idx+12] = pos.z + coords[face][12];
            vertex_data[idx+13] = p * t + p * coords[face][13];
            vertex_data[idx+14] = p * t + p * coords[face][14];
            vertex_data[idx+15] = pos.x + coords[face][15];
            vertex_data[idx+16] = pos.y + coords[face][16];
            vertex_data[idx+17] = pos.z + coords[face][17];
            vertex_data[idx+18] = p * t + p * coords[face][18];
            vertex_data[idx+19] = p * t + p * coords[face][19];
            vertex_data[idx+20] = pos.x + coords[face][20];
            vertex_data[idx+21] = pos.y + coords[face][21];
            vertex_data[idx+22] = pos.z + coords[face][22];
            vertex_data[idx+23] = p * t + p * coords[face][23];
            vertex_data[idx+24] = p * t + p * coords[face][24];
            vertex_data[idx+25] = pos.x + coords[face][25];
            vertex_data[idx+26] = pos.y + coords[face][26];
            vertex_data[idx+27] = pos.z + coords[face][27];
            vertex_data[idx+28] = p * t + p * coords[face][28];
            vertex_data[idx+29] = p * t + p * coords[face][29];        
            idx += 30;
        }    
    }
    bindVAO(VAO);
    bindVBO(VBO);
    bindVBOData(num_faces * 6 * 5 * sizeof(float), vertex_data);
}
