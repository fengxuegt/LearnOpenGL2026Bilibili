//
// Created by fengxuegt on 2026/3/11.
//

#include "cameracontrol.h"

void CameraControl::onMouse(int button, int action, double xpos, double ypos) {
    bool pressed = action == GLFW_PRESS ? true : false;
    if (pressed) {
        mCurrentX = xpos;
        mCurrentY = ypos;
    }
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftMouseButtonDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightMouseButtonDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleMouseButtonDown = pressed;
            break;
    }
}

void CameraControl::onCursor(float xpos, float ypos) {
}

void CameraControl::onKey(int key, int action, int mods) {
    if (action == GLFW_REPEAT) {
        return;
    }
    bool pressed = action == GLFW_PRESS ? true : false;
    mKeyMap[key] = pressed;
}

void CameraControl::onScroll(double yoffset) {
}

void CameraControl::update() {
}

CameraControl::CameraControl() {
}

CameraControl::~CameraControl() {
}
