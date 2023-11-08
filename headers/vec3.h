#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <cmath>

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
    vec3f operator+(const vec3f& other)
    {
        return vec3f(x + other.x, y + other.y, z + other.z);
    }
    void operator+=(const vec3f& other)
    {
        x += other.x; y += other.y; z += other.z;
    }
    vec3f operator-(const vec3f& other)
    {
        return vec3f(x - other.x, y - other.y, z - other.z);
    }
    void operator-=(const vec3f& other)
    {
        x -= other.x; y -= other.y; z -= other.z;
    }
    vec3f operator*(const vec3f& other)
    {
        float _x = y * other.z - z * other.y;
        float _y = z * other.x - x * other.z;
        float _z = x * other.y - y * other.x;
        return vec3f(_x, _y, _z);
    }
    vec3f operator*(const float& num)
    {
        return vec3f(x * num, y * num, z * num);
    }
};

inline vec3f normalize(vec3f vec)
{
    float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    if (mag != 0)
        return vec3f(vec.x / mag, vec.y / mag, vec.z / mag);
    return vec3f();
}

inline std::ostream& operator<<(std::ostream& out, vec3f& vec)
{
    float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ") [" << mag << "]";
    return out;
}

#endif /* VEC3_H */