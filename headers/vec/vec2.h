#pragma once
#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <cmath>

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
    vec2f operator*(const float& num)
    {
        return vec2f(x * num, y * num);
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

inline vec2f normalize(vec2f vec)
{
    float mag = sqrt(vec.x*vec.x + vec.y*vec.y);
    if (mag != 0)
        return vec2f(vec.x / mag, vec.y / mag);
    return vec2f();
}


inline std::ostream& operator<<(std::ostream& out, vec2f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
}

inline std::ostream& operator<<(std::ostream& out, vec2i& vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
}

#endif /* VEC2_H */