#ifndef SUDOKUCUBE_H
#define SUDOKUCUBE_H

#include "model.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "shader.h"

class SudokuCube {
public:
    SudokuCube();
    ~SudokuCube();
    void drawFaces(Shader& shader, int activeLayer, int axis); // axis: 0=X, 1=Y, 2=Z
    void drawEdges();
    void rotate(const glm::quat& rotation);

private:
    std::vector<std::vector<std::vector<Model*>>> cells; // 9x9x9 grid
    glm::quat globalRotation;
};

#endif

