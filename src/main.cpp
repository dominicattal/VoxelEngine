#include <glad.h>
#include <glfw.h>
#include <iostream>
#include <cmath>
#include <vec3.h>
#include "error.h"
#include "Shader.h"
#include "Camera.h"
#include "Rect.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int actions, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void updateProjectionMatrix(Shader shader);
void updateViewMatrix(Shader shader);
void updateDeltaTime();

int window_width  = 800;
int window_height = 600;
float dt = 0, frame_time;
Camera camera;

float mouse_x = window_width / 2;
float mouse_y = window_height / 2;

int main() 
{
    // initialize glfw
    if (!glfwInit())
        throwError(1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // initalize window
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Voxels", NULL, NULL);
    if (window == NULL)
        throwError(2);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    // initalize glad
    if (!gladLoadGL(glfwGetProcAddress))
        throwError(3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  

    Shader shader("shaders/vertex.sl", "shaders/fragment.sl");

    Rect square("assets/test.jpg", &shader, window_width / window_height);

    frame_time = glfwGetTime();

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    unsigned int viewID = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
    updateViewMatrix(shader);
    updateProjectionMatrix(shader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        square.draw();
        updateDeltaTime();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 1;
}

void processInput(GLFWwindow* window)
{
    // Handles keyboard inputs
    vec3f moving;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moving.z += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moving.z -= 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moving.x -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moving.x += 1;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        moving.y -= 1;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        moving.y += 1;
    camera.move(moving, dt);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Change viewport when window resized
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << 1 / dt << std::endl;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        std::cout << 1 / dt << std::endl;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    float x_offset = xpos - mouse_x;
    float y_offset = ypos - mouse_y;
    mouse_x = xpos;
    mouse_y = ypos;
    camera.turn(x_offset, y_offset);
}

void updateProjectionMatrix(Shader shader)
{
    // update shader projection matrix
    shader.use();
    float aspect_ratio = (float)window_width / window_height;
    float fov = camera.fov;
    float near_clip_dis = 0.1f; 
    float far_clip_dis = 100.0f; 
    float v1, v2, v3, v4;
    float e = 1 / tan(fov / 2);
    v1 = e / aspect_ratio;
    v2 = e;
    v3 = (near_clip_dis + far_clip_dis) / (near_clip_dis - far_clip_dis);
    v4 = (2 * far_clip_dis * near_clip_dis) / (near_clip_dis - far_clip_dis);
    const float proj[] = {
        v1, 0, 0, 0,
        0, v2, 0, 0,
        0, 0, v3, -1,
        0, 0, v4, 0
    };
    unsigned int projID = glGetUniformLocation(shader.ID, "perspective");
    glUniformMatrix4fv(projID, 1, GL_FALSE, proj);
}

void updateViewMatrix(Shader shader)
{
    shader.use();
    float rx, ry, rz; 
    float ux, uy, uz; 
    float dx, dy, dz; 
    float px, py, pz; 
    float k1, k2, k3;
    // ----
    rx = camera.right.x; ry = camera.right.y; rz = camera.right.z;
    ux = camera.up.x; uy = camera.up.y; uz = camera.up.z;
    dx = camera.facing.x; dy = camera.facing.y; dz = camera.facing.z;
    px = -camera.position.x; py = -camera.position.y; pz = -camera.position.z;
    // ----
    rx = 1; ry = 0; rz = 0;
    ux =  0; uy = 1; uz = 0;
    px =  0; py = 0; pz = 3;
    dx = 0; dy = 0; dz = 1;
    k1 = px * rx + py * ry + pz * rz;
    k2 = px * ux + py * uy + pz * uz;
    k3 = px * dx + py * dy + pz * dz;
    float view[] = {
        rx, ux, dx, 0,
        ry, uy, dy, 0,
        rz, uz, dz, 0,
        -k1, -k2, -k3, 1
    };
    unsigned int viewID = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewID, 1, GL_FALSE, view);
    glm::mat4 view2 = glm::lookAt(glm::vec3(0, 0, 3.0f),
                                  glm::vec3(0, 0, 2.0f),
                                  glm::vec3(0, 1.0f, 0));
    //glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view2));
    for (int i = 0; i < 16; i++) 
    { 
        std::cout << view[i] - glm::value_ptr(view2)[i] << std::endl;
    }
    //std::cout << "---" << std::endl;
}

void updateDeltaTime()
{
    float current_time = glfwGetTime();
    dt = current_time - frame_time;
    frame_time = current_time;
}
