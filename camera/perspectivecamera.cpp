//
// Created by fengxuegt on 2026/3/11.
//

#include "perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera() {
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) {
    mFov = fov;
    mAspect = aspect;
    mNear = near;
    mFar = far;
}

PerspectiveCamera::~PerspectiveCamera() {
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
}
