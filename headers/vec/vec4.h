#pragma once
#ifndef VEC4_H
#define VEC4_H

#include <ostream>

class vec4f 
{
public:
    float x, y, z, w;
    vec4f(float _x, float _y, float _z, float _w)
    {
        x = _x; y = _y; z = _z; w = _w;
    }
    vec4f() 
    { 
        x = 0; y = 0; z = 0; w = 0;
    }
};

class vec4i
{
public:
    int x, y, z, w;
    vec4i(int _x, int _y, int _z, int _w)
    {
        x = _x; y = _y; z = _z; w = _w;
    }
    vec4i() 
    { 
        x = 0; y = 0; z = 0; w = 0;
    }
};

std::ostream& operator<<(std::ostream& out, vec4f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, vec4i& vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return out;
}

#endif /* vec4_H */