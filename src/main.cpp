#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "shader.h"
#include "camera.h"
#include "model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void rotateCubeWithMouse(GLFWwindow* window, glm::mat4& model);

// Variables globales para la rotación del cubo
bool rotateCube = false;
double lastMouseX = 0, lastMouseY = 0;
glm::quat rotationX = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), rotationY = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cubo 3D", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Configurar shaders
    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    // Configurar cámara
    Camera camera(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    // Configurar modelo (cubo)
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4};
    Model cube(vertices, indices);

    // Habilitar prueba de profundidad
    glEnable(GL_DEPTH_TEST);

    // Bucle principal
    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Limpiar el búfer de color y profundidad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rotar el cubo con el mouse
        glm::mat4 model = glm::mat4(1.0f);
        rotateCubeWithMouse(window, model);
        cube.setTransform(model);

        // Dibujar el cubo
        shader.use();
        shader.setMat4("model", model);
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", camera.getProjectionMatrix());
        shader.setColor("color", glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));  // Color naranja
        cube.drawFaces();

        shader.setColor("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));  // Color negro
        cube.drawEdges();

        // Intercambiar búferes y procesar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Liberar recursos
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        rotateCube = true;
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        rotateCube = false;
    }
}

void rotateCubeWithMouse(GLFWwindow* window, glm::mat4& model) {
    if (rotateCube) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xoffset = lastMouseX - xpos;  // Invertir el signo
        float yoffset = ypos - lastMouseY;  // Invertir el signo
        lastMouseX = xpos;
        lastMouseY = ypos;

        float sensitivity = 0.005f;  // Ajusta este valor según sea necesario
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        // Crear cuaterniones para las rotaciones en X e Y
        glm::quat deltaRotationX = glm::angleAxis(yoffset, glm::vec3(1.0f, 0.0f, 0.0f));  // Rotar en X
        glm::quat deltaRotationY = glm::angleAxis(xoffset, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotar en Y

        // Aplicar las rotaciones acumuladas
        rotationX = deltaRotationX * rotationX;
        rotationY = deltaRotationY * rotationY;
    }

    // Combinar las rotaciones en X e Y
    glm::quat finalRotation = rotationY * rotationX;

    // Convertir el cuaternión a una matriz de transformación
    model = glm::mat4_cast(finalRotation);
}