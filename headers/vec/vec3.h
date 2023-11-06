#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <ostream>

class vec3f 
{
public:
    float x, y, z;
    vec3f(float _x, float _y, float _z)
    {
        x = _x; y = _y; z = _z;
    }
    vec3f() 
    { 
        x = 0; y = 0; z = 0;
    }
};

class vec3i
{
public:
    int x, y, z;
    vec3i(int _x, int _y, int _z)
    {
        x = _x; y = _y; z = _z;
    }
    vec3i() 
    { 
        x = 0; y = 0; z = 0;
    }
};

inline std::ostream& operator<<(std::ostream& out, vec3f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

inline std::ostream& operator<<(std::ostream& out, vec3i& vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

#endif /* VEC3_H */