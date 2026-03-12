//
// Created by fengxuegt on 2026/3/12.
//

#include "trackballcameracontrol.h"

TrackBallCameraControl::TrackBallCameraControl() {
}

TrackBallCameraControl::~TrackBallCameraControl() {
}

void TrackBallCameraControl::onCursor(float xpos, float ypos) {
    if (mLeftMouseButtonDown) {

        // 计算经线和纬线的增量角度
        float deltaX = (xpos - mCurrentX) * mSensitivity;
        float deltaY = (ypos - mCurrentY) * mSensitivity;

        // pitch
        pitch(-deltaY);

        // yaw
        yaw(-deltaX);

    } else if (mMiddleMouseButtonDown) {
        float deltaX = (xpos - mCurrentX) * moveSpeed;
        float deltaY = (ypos - mCurrentY) * moveSpeed;

        mCamera->mPosition += mCamera->mUp * deltaY;
        mCamera->mPosition -= mCamera->mRight * deltaX;

    }
    mCurrentX = xpos;
    mCurrentY = ypos;
}

void TrackBallCameraControl::onScroll(double yoffset) {
    mCamera->scale(yoffset * mScaleSpeed);
}

void TrackBallCameraControl::pitch(float angle) {
    // 围绕mRight旋转
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    // 影响当前相机的up向量和位置
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f); // vect 赋值给vec3是没有问题的
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);

}

void TrackBallCameraControl::yaw(float angle) {
    // 围绕y轴旋转
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
    mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}
