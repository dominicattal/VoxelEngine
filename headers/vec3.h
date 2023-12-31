#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <cmath>

#define chunk_size 16

struct vec3f 
{
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
    void operator*=(const vec3f& other)
    {
        x = y * other.z - z * other.y;
        y = z * other.x - x * other.z;
        z = x * other.y - y * other.x;
    }
    vec3f operator*(const float& num)
    {
        return vec3f(x * num, y * num, z * num);
    }
    void operator*=(const float& num)
    {
        x *= num; y *= num; z *= num;
    }
};

inline bool operator==(const vec3f& vec1, const vec3f& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

inline vec3f floor(const vec3f& vec)
{
    return vec3f(floor(vec.x), floor(vec.y), floor(vec.z));
}

inline std::pair<int, int> toChunkCoords(const vec3f& vec)
{
    int vec_x = floor(vec.x);
    int vec_z = floor(vec.z);
    std::pair<int, int> chunk;
    if (vec_x >= 0)
        chunk.first = vec_x / chunk_size;
    else
        chunk.first = vec_x / chunk_size - 1;
    if (vec_z >= 0)
        chunk.second = vec_z / chunk_size;
    else
        chunk.second = vec_z / chunk_size - 1;
    return chunk;
}

inline vec3f normalize(vec3f vec)
{
    float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    if (mag != 0)
        return vec3f(vec.x / mag, vec.y / mag, vec.z / mag);
    return vec3f();
}

inline std::ostream& operator<<(std::ostream& out, const vec3f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

template <>
struct std::hash<vec3f>
{
  std::size_t operator()(const vec3f& k) const
  {
    return ((std::hash<float>()(k.x)
             ^ (std::hash<float>()(k.y) << 1)) >> 1)
             ^ (std::hash<float>()(k.z) << 1);
  }
};

template <>
struct std::hash<std::pair<int, int>>
{
  std::size_t operator()(const std::pair<int, int>& p) const
  {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

#endif /* VEC3_H */