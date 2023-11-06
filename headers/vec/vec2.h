#pragma once
#ifndef VEC2_H
#define VEC2_H

#include <ostream>

class vec2f 
{
public:
    float x, y;
    vec2f(float _x, float _y)
    {
        x = _x; y = _y;
    }
    vec2f() 
    { 
        x = 0; y = 0; 
    }
};

class vec2i
{
public:
    int x, y;
    vec2i(int _x, int _y)
    {
        x = _x; y = _y;
    }
    vec2i() 
    { 
        x = 0; y = 0; 
    }
};

std::ostream& operator<<(std::ostream& out, vec2f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, vec2i& vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
}

#endif /* VEC2_H */