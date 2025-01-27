#define GLM_FORCE_CTOR_INIT
#include "sudokucube.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

std::vector<float> verticesCube = {
    -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
std::vector<unsigned int> indicesCube = {
    0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5,
    4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4};

SudokuCube::SudokuCube() {
    // Initialize grid with actual Model objects
    cells.resize(9, std::vector<std::vector<Model*>>(9, std::vector<Model*>(9, nullptr)));
    
    // Define cube geometry once
    std::vector<float> vertices = verticesCube;
    std::vector<unsigned int> indices = indicesCube;

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            for (int z = 0; z < 9; z++) {
                // Create new Model instance with parameters
                cells[x][y][z] = new Model(vertices, indices);
                
                // Set initial transform
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x-4, y-4, z-4));
                cells[x][y][z]->setTransform(model);
            }
        }
    }
}

void SudokuCube::drawFaces(Shader& shader, int activeLayer, int axis) {
    glm::mat4 globalRotMatrix = glm::mat4(1.0f) * glm::mat4_cast(globalRotation);
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            for (int z = 0; z < 9; z++) {

                bool isVisible = false;
                switch (axis)
                {
                case 0:
                    isVisible = (x == activeLayer);
                    break; // X-axis layer
                case 1:
                    isVisible = (y == activeLayer);
                    break; // Y-axis layer
                case 2:
                    isVisible = (z == activeLayer);
                    break; // Z-axis layer
                }
                if (isVisible) {
                    // Ensure both matrices are initialized
                    glm::mat4 cellTransform = cells[x][y][z]->getTransform();
                    glm::mat4 modelMatrix = globalRotMatrix * cellTransform;
                    shader.setMat4("model", modelMatrix);
                    cells[x][y][z]->draw();
                }

            }
        }
    }
}

SudokuCube::~SudokuCube() {
    for (auto& x : cells) {
        for (auto& y : x) {
            for (auto& z : y) {
                delete z; // Free allocated memory
            }
        }
    }
}


void SudokuCube::rotate(const glm::quat &rotation)
{
    globalRotation = rotation * globalRotation;
}