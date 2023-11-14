#include "camera.h"
#include "globals.h"
#include <iostream>

Camera::Camera()
{
    position     = vec3f(8.5f, 0.0f, 3.0f);
    facing       = vec3f(1, 0, 0);
    right        = vec3f(0, 0, -1);
    up           = vec3f(0, 1, 0);
    yaw          = 0.0;
    pitch        = 0.0;
    fov          = PI / 4;
    aspect_ratio = (float)window_width / window_height; 
    sensitivity  = 0.001;
    speed        = 20;
}

void Camera::linkShader(Shader shader)
{
    shader.use();
    viewID = glGetUniformLocation(shader.ID, "view");
    projID = glGetUniformLocation(shader.ID, "perspective");
    updateViewMatrix();
    updateProjectionMatrix();
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

void Camera::move(vec3f moving)
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

void Camera::updateProjectionMatrix()
{
    float near_clip_dis = 0.1f; 
    float far_clip_dis = 200.0f; 
    float v1, v2, v3, v4;
    v1 = 1 / (aspect_ratio * tan(fov / 2));
    v2 = 1 / (tan(fov / 2));
    v3 = (-near_clip_dis - far_clip_dis) / (near_clip_dis - far_clip_dis);
    v4 = (2 * far_clip_dis * near_clip_dis) / (near_clip_dis - far_clip_dis);
    const float proj[] = {
        v1, 0, 0, 0,
        0, v2, 0, 0,
        0, 0, v3, 1,
        0, 0, v4, 0
    };
    glUniformMatrix4fv(projID, 1, GL_FALSE, proj);
}
