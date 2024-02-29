#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "model.hpp"
//#include "camera_exercises.hpp"

// Create camera object
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// Timers
float currentFrame = 0.0f;
float lastFrame = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Transformations", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    
    // Use back face culling
    glEnable(GL_CULL_FACE);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
                     
    // Dark grey background
    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
    
    // Compile shader program
    GLuint shaderID = LoadShaders("vertexShader.vert", "fragmentShader.frag");
    
    // Get the handles for the shader uniforms
    GLuint modelID = glGetUniformLocation(shaderID, "model");
    GLuint viewID = glGetUniformLocation(shaderID, "view");
    GLuint projectionID = glGetUniformLocation(shaderID, "projection");
    
    // Load suzanne object
    model suzanne("teapot.obj");
    suzanne.loadTexture("blue.bmp");
    
    do {
        // Update timers
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Get the view and projection matrices from the camera library
        camera.calculateMatrices(window, deltaTime);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();
        
        // Calculate model matrix
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = translate * rotate * scale;
        
        // Send the model, view and projection matrices to the shader
        glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
        
        // Draw object
        suzanne.draw(shaderID);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup
    glDeleteProgram(shaderID);
    suzanne.deleteBuffers();
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
