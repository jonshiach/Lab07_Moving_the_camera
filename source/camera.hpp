#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
public:
    // Projection parameters
    float fov = glm::radians(45.0f);
    float aspect = 1024.0f / 768.0f;
    float near = 0.02f;
    float far = 100.0f;
    
    // Camera vectors
    glm::vec3 position;
    glm::vec3 worldUp;
    
    // Transformation matrices
    glm::mat4 view;
    glm::mat4 projection;
    
    // Constructor
    Camera(const glm::vec3 Position);
    
    // Methods
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void calculateMatrices();
};
