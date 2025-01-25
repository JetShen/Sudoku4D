#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setColor(const std::string &name, const glm::vec4 &color) const;
    unsigned int ID;
};

#endif