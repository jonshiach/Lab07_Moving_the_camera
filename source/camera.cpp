#include <cmath>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

// Declare matrices
glm::mat4 view, projection;

// Declare view defaults
glm::vec3 camera = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 target = glm::vec3(0.0f, 0.0f, -4.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Declare projection defaults
float fov = glm::radians(45.0f);
float aspect = 1024.0f / 768.0f;
float near = 0.02f;
float far = 100.0f;

// Functions
glm::mat4 getViewMatrix()
{
    return view;
}

glm::mat4 getProjectionMatrix()
{
    return projection;
}

void pointCamera(GLFWwindow* window)
{
    // Calculate view matrix
    view = glm::lookAt(camera, target, worldUp);
    
    // Calculate projection matrix
    projection = glm::perspective(fov, aspect, near, far);
    
}
