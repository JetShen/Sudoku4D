#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspectRatio, float near, float far);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void setPosition(glm::vec3 position);
    void setTarget(glm::vec3 target);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float fov;
    float aspectRatio;
    float near;
    float far;
};

#endif