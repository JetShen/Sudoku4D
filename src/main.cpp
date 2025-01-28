#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "sudokucube.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow* window, SudokuCube& sudokuCube, int& activeLayer, int& axis, double& lastLayerChangeTime);

int main()
{
    // Initialize GLFW and create window
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "3D Sudoku", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Load shaders
    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    // Define cube geometry
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f};

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4};

    SudokuCube sudokuCube;

    // Camera setup: Move camera further back to see the grid
    Camera camera(glm::vec3(5.0f, 15.0f, 15.0f), 800.0f / 600.0f);

    glEnable(GL_DEPTH_TEST);

    // Initialize active layer and axis
    int activeLayer = 4; // Start with the middle layer
    int axis = 1;
    
    double lastLayerChangeTime = glfwGetTime();
    const double layerChangeCooldown = 0.2;     
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, sudokuCube, activeLayer, axis, lastLayerChangeTime);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        // Set the color uniform (add this line)
        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader.setMat4("view", camera.getView());
        shader.setMat4("proj", camera.getProj());

        sudokuCube.drawFaces(shader, activeLayer, axis); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window, SudokuCube& sudokuCube, int& activeLayer, int& axis, double& lastLayerChangeTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float rotationSpeed = 1.0f;

    // Rotate around the Y-axis (vertical) for a/d 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        sudokuCube.rotate(glm::quat(glm::vec3(0.0f, glm::radians(rotationSpeed), 0.0f)));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        sudokuCube.rotate(glm::quat(glm::vec3(0.0f, glm::radians(-rotationSpeed), 0.0f)));
    }

    // Rotate around the X-axis (horizontal) for w/s
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        sudokuCube.rotate(glm::quat(glm::vec3(glm::radians(rotationSpeed), 0.0f, 0.0f)));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        sudokuCube.rotate(glm::quat(glm::vec3(glm::radians(-rotationSpeed), 0.0f, 0.0f)));
    }

    // Time-based layer navigation
    double currentTime = glfwGetTime();
    if (currentTime - lastLayerChangeTime >= 0.2) { // Cooldown of 0.2 seconds
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            activeLayer = (activeLayer + 1) % 9; // Move to the next layer
            lastLayerChangeTime = currentTime;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            activeLayer = (activeLayer - 1 + 9) % 9; // Move to the previous layer
            lastLayerChangeTime = currentTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            axis = (axis - 1 + 3) % 3; // Switch to the previous axis (X, Y, Z)
            lastLayerChangeTime = currentTime;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            axis = (axis + 1) % 3; // Switch to the next axis (X, Y, Z)
            lastLayerChangeTime = currentTime;
        }
    }
}