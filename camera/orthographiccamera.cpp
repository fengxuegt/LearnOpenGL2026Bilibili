//
// Created by fengxuegt on 2026/3/11.
//

#include "orthographiccamera.h"

OrthographicCamera::OrthographicCamera() {
}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) {
    mLeft = left;
    mRight = right;
    mBottom = bottom;
    mTop = top;
    mNear = near;
    mFar = far;
}

OrthographicCamera::~OrthographicCamera() {

}

glm::mat4 OrthographicCamera::getProjectionMatrix() {
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}

void OrthographicCamera::scale(float scale) {
    Camera::scale(scale);
}
