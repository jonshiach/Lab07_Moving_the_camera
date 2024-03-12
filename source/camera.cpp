#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

Camera::Camera(const glm::vec3 Position)
{
    position = Position;
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return view;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projection;
}

void Camera::calculateMatrices()
{
    // Calculate view matrix
    view = glm::lookAt(position, target, worldUp);
    
    // Calculate projection matrix
    projection = glm::perspective(fov, aspect, near, far);
}
