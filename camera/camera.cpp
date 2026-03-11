//
// Created by fengxuegt on 2026/3/11.
//

#include "camera.h"


Camera::Camera() {
}

Camera::~Camera() {
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 fornt = glm::cross(mUp, mRight);
    glm::vec3 center = mPosition + fornt;
    return glm::lookAt(mPosition, center, mUp);
}
