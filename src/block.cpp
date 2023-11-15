#include "block.h"
#include <iostream>

std::unordered_map<blocktype, std::string> type_to_string = 
{
    {TYPE1, "type1"},
    {TYPE2, "type2"}
};

std::unordered_map<Face, std::string> face_to_string =
{
    {LEFT, "left"},
    {RIGHT, "right"},
    {FRONT, "front"},
    {BACK, "back"},
    {TOP, "top"},
    {BOTTOM, "bottom"}
};

std::unordered_map<vec3f, Block*>* blocks = new std::unordered_map<vec3f, Block*>();
std::unordered_map<blocktype, TypeTextures>* textures = new std::unordered_map<blocktype, TypeTextures>();
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

void initalizeBlocks()
{
    coords[LEFT]   = left;
    coords[RIGHT]  = right;
    coords[FRONT]  = front;
    coords[BACK]   = back;
    coords[TOP]    = top;
    coords[BOTTOM] = bottom;

    for (int type = 0; type < NUM_TYPES; type++)
    {
        TypeTextures type_texs(static_cast<blocktype>(type));
        textures->insert({static_cast<blocktype>(type), type_texs});
    }

    int l = 0;
    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 101; k++)
            {
                if (l % 100000 == 0)
                {
                    std::cout << l << std::endl;
                }
                if (l % 2 == 0)
                    createBlock(TYPE1, vec3f(i, -j-1, k));
                else
                    createBlock(TYPE2, vec3f(i, -j-1, k));
                l++;
            }
        }
    }
 
    for (int type = 0; type < NUM_TYPES; type++)
    {
        TypeTextures type_texs = textures->at(static_cast<blocktype>(type));
        for (int face = 0; face < 6; face++)
        {
            type_texs.updateVertexData(static_cast<Face>(face));
        }
    }
}

void drawBlocks()
{
    for (auto pair : *textures)
    {
        pair.second.drawFaces();
    }
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
        TypeTextures texture = textures->at(block->type);
        for (int i = 0; i < 6; i++)
        {
            Face face = static_cast<Face>(i);
            vec3f other_pos = position + dirs[face];
            Face other_face = opposite_face[face];
            if (blocks->count(other_pos))
            {
                Block* other_block = blocks->at(other_pos);
                TypeTextures other_texture = textures->at(other_block->type);
                other_texture.erase(other_pos, other_face);
            }
            else
            {
                texture.insert(position, face);
            }
        }
    }
}

Block::Block(blocktype type_)
{
    type = type_;
}

TypeTextures::TypeTextures(blocktype type)
{
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenTextures(6, TEXs);
    for (int i = 0; i < 6; i++)
    {  
        Face face = static_cast<Face>(i);  
        bindTexture(TEXs[face]);
        std::string path = "assets/" + type_to_string[type] + "/" + 
            type_to_string[type] + "_" + face_to_string[face] + ".png";
        bindTextureData(path.c_str());
        vertex_data[face] = new float[0];
        faces[face] = new std::unordered_set<vec3f>();
    }
}

void TypeTextures::updateVertexData(Face face)
{
    delete[] vertex_data[face];
    int size = faces[face]->size();
    vertex_data[face] = new float[size * 6 * 5];
    int idx = 0;
    for (auto pos : *(faces[face]))
    {
        vertex_data[face][idx]    = pos.x + coords[face][0];
        vertex_data[face][idx+1]  = pos.y + coords[face][1];
        vertex_data[face][idx+2]  = pos.z + coords[face][2];
        vertex_data[face][idx+3]  = coords[face][3];
        vertex_data[face][idx+4]  = coords[face][4];
        vertex_data[face][idx+5]  = pos.x + coords[face][5];
        vertex_data[face][idx+6]  = pos.y + coords[face][6];
        vertex_data[face][idx+7]  = pos.z + coords[face][7];
        vertex_data[face][idx+8]  = coords[face][8];
        vertex_data[face][idx+9]  = coords[face][9];
        vertex_data[face][idx+10] = pos.x + coords[face][10];
        vertex_data[face][idx+11] = pos.y + coords[face][11];
        vertex_data[face][idx+12] = pos.z + coords[face][12];
        vertex_data[face][idx+13] = coords[face][13];
        vertex_data[face][idx+14] = coords[face][14];
        vertex_data[face][idx+15] = pos.x + coords[face][15];
        vertex_data[face][idx+16] = pos.y + coords[face][16];
        vertex_data[face][idx+17] = pos.z + coords[face][17];
        vertex_data[face][idx+18] = coords[face][18];
        vertex_data[face][idx+19] = coords[face][19];
        vertex_data[face][idx+20] = pos.x + coords[face][20];
        vertex_data[face][idx+21] = pos.y + coords[face][21];
        vertex_data[face][idx+22] = pos.z + coords[face][22];
        vertex_data[face][idx+23] = coords[face][23];
        vertex_data[face][idx+24] = coords[face][24];
        vertex_data[face][idx+25] = pos.x + coords[face][25];
        vertex_data[face][idx+26] = pos.y + coords[face][26];
        vertex_data[face][idx+27] = pos.z + coords[face][27];
        vertex_data[face][idx+28] = coords[face][28];
        vertex_data[face][idx+29] = coords[face][29];        
        idx += 30;
    }

    bindVAO(VAOs[face]);
    bindVBO(VBOs[face]);
    bindVBOData(size * 6 * 5 * sizeof(float), vertex_data[face]);
}

void TypeTextures::drawFaces()
{
    for (int i = 0; i < 6; i++)
    {
        bindVAO(VAOs[i]);
        bindTexture(TEXs[i]);
        drawTriangles(faces[i]->size() * 6);
    }
}

void TypeTextures::insert(vec3f position, Face face)
{
    faces[face]->insert(position);
}

void TypeTextures::erase(vec3f position, Face face)
{
    faces[face]->erase(position);
}