#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

class Model {
public:
    Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    void draw() const;
    void setTransform(const glm::mat4& transform);
    glm::mat4 getTransform() const { return modelMatrix; }
private:
    GLuint VAO, VBO, EBO;
    size_t indexCount;
    glm::mat4 modelMatrix;
};