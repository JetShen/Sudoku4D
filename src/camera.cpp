#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspectRatio, float near, float far)
    : position(position), target(target), up(up), fov(fov), aspectRatio(aspectRatio), near(near), far(far) {}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

void Camera::setTarget(glm::vec3 target) {
    this->target = target;
}