#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Model {
public:
    Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    void draw();
    void setTransform(glm::mat4 transform);

private:
    unsigned int VAO, VBO, EBO;
    glm::mat4 transform;
};

#endif