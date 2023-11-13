#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "error.h"

struct Shader 
{
    unsigned int ID;
    Shader(const char* vertex_path, const char* fragment_path);
    void use();
};

#endif /* SHADER_H */