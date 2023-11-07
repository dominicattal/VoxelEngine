#include "Camera.h"

Camera::Camera()
{
    position = vec3f(0.0f, 0.0f, 3.0f);
    direction = vec3f(0.0f, 0.0f, -1.0f);
    fov = 0.785398;
}