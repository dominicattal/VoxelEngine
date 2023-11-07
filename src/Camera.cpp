#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    position = vec3f(0.0f, 0.0f, 3.0f);
    direction = vec3f(0.0f, 0.0f, -1.0f);
    update();
    fov = 0.785398;
}

void Camera::update()
{
    vec3f y = vec3f(0.0f, 1.0f, 0.0f);
    right = normalize(y * direction);
    up = direction * right;
}
