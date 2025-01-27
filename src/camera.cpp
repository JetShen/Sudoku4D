#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float aspect) : position(position) {
    view = glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}

glm::mat4 Camera::getView() const { return view; }
glm::mat4 Camera::getProj() const { return projection; }

void Camera::updateAspect(float aspect) {
    projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}