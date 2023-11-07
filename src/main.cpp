#include <glad.h>
#include <glfw.h>
#include <iostream>
#include <vec/vec2.h>
#include <vec/vec3.h>
#include <vec/vec4.h>
#include "error.h"
#include "Shader.h"
#include "Camera.h"
#include "Rect.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int actions, int mods);
void updateProjectionMatrix(Shader shader);
void updateViewMatrix(Shader shaders);
void updateDeltaTime();

int window_width  = 800;
int window_height = 800;
float dt = 0, frame_time;
float fov = 0.785398; 
Camera camera;

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

    Shader shader("shaders/vertex.sl", "shaders/fragment.sl");

    Rect square("assets/test.jpg", &shader);

    frame_time = glfwGetTime();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateProjectionMatrix(shader);
        updateViewMatrix(shader);
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position.y -= 0.1 * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position.y += 0.1 * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position.x += 0.1 * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position.x -= 0.1 * dt;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.position.z -= 0.1 * dt;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.position.z += 0.1 * dt;
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

void updateProjectionMatrix(Shader shader)
{
    // update shader projection matrix
    float aspect_ratio = window_width / window_height;
    float near_clip_dis = 0.1f; 
    float far_clip_dis = 100.0f; 
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
    unsigned int projID = glGetUniformLocation(shader.ID, "perspective");
    glUniformMatrix4fv(projID, 1, GL_FALSE, proj);
}

void updateViewMatrix(Shader shader)
{
    const float view[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        camera.position.x, camera.position.y, camera.position.z, 1
    };
    unsigned int viewID = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewID, 1, GL_FALSE, view);
}

void updateDeltaTime()
{
    float current_time = glfwGetTime();
    dt = current_time - frame_time;
    frame_time = current_time;
}