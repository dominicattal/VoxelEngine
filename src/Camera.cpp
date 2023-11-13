#include "camera.h"
#include <iostream>

Camera::Camera()
{
    position = vec3f(8.5f, 0.0f, 3.0f);
    facing   = vec3f(1, 0, 0);
    right    = vec3f(0, 0, -1);
    up       = vec3f(0, 1, 0);
    yaw = 0.0;
    pitch = 0.0;
    fov = 0.785398;
    sensitivity = 0.001;
    speed = 20;
}

void Camera::linkShader(Shader shader)
{
    viewID = glGetUniformLocation(shader.ID, "view");
}

void Camera::turn(float x_offset, float y_offset)
{
    yaw += x_offset * sensitivity;
    pitch += y_offset * sensitivity;

    if(pitch > 1.56)
        pitch = 1.56;
    if(pitch < -1.56)
        pitch = -1.56;

    facing.x = cos(yaw) * cos(pitch);
    facing.y = sin(pitch);
    facing.z = sin(yaw) * cos(pitch);
    facing = normalize(facing);

    vec3f y_axis = vec3f(0.0f, 1.0f, 0.0f);
    right = normalize(y_axis * facing);
    up = facing * right;

    updateViewMatrix();
}

void Camera::move(vec3f moving, float dt)
{
    normalize(moving);
    vec3f direction;
    direction += right  * moving.x;
    direction += up     * moving.y;
    direction += facing * moving.z;
    //direction.x += facing.x * moving.z;
    //direction.z += facing.z * moving.z;
    //direction.x += right.x  * moving.x;
    //direction.z += right.z  * moving.x;
    direction = normalize(direction);
    position += direction * speed * dt;
    updateViewMatrix();
}

void Camera::updateViewMatrix()
{
    float rx, ry, rz; 
    float ux, uy, uz; 
    float dx, dy, dz; 
    float px, py, pz; 
    float k1, k2, k3;
    rx = right.x; ry = right.y; rz = right.z;
    ux = up.x; uy = up.y; uz = up.z;
    dx = facing.x; dy = facing.y; dz = facing.z;
    px = -position.x; py = -(position.y + 0.5); pz = -position.z;
    k1 = px * rx + py * ry + pz * rz;
    k2 = px * ux + py * uy + pz * uz;
    k3 = px * dx + py * dy + pz * dz;
    float view[] = {
        rx, ux, dx, 0,
        ry, uy, dy, 0,
        rz, uz, dz, 0,
        k1, k2, k3, 1
    };
    glUniformMatrix4fv(viewID, 1, GL_FALSE, view);
}
