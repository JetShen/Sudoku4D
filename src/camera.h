#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 position, float aspect);
    glm::mat4 getView() const;
    glm::mat4 getProj() const;
    void updateAspect(float aspect);

private:
    glm::vec3 position;
    glm::mat4 view;
    glm::mat4 projection;
};