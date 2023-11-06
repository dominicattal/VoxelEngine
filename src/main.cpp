#include <glad.h>
#include <glfw.h>
#include <iostream>
#include <vec/vec2.h>
#include <vec/vec3.h>
#include <vec/vec4.h>
#include "error.h"
#include "Shader.h"
#include "Rect.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int actions, int mods);
void updateDeltaTime();

int window_width  = 800;
int window_height = 800;
float dt = 0, frame_time;

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

    vec3f camera_pos(0.0f, 0.0f, 3.0f);
    vec3f camera_target(0.0f, 0.0f, 0.0f);
    vec3f camera_direction = normalize(camera_target - camera_pos);
    
    vec3f test1(1, 2, 3);
    vec3f test2(4, 5, 6);
    vec3f test3 = normalize(test1 * test2);
    std::cout << test3 << std::endl;
    
    Rect square("assets/test.png", shader);

    frame_time = glfwGetTime();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
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
}

void updateDeltaTime()
{
    float current_time = glfwGetTime();
    dt = current_time - frame_time;
    frame_time = current_time;
}