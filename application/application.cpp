//
// Created by fengxuegt on 2026/2/27.
//

#include "application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Application::getCurrentXYPosition(double *x, double *y) {
    glfwGetCursorPos(mWindow, x, y);
}

GLFWwindow* Application::getWindow() {
    return mWindow;
}

bool Application::init(const char* title, int width, int height) {
    mWidth = width;
    mHeight = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!mWindow) {
        return false;
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, frameSizeCallback);
    glfwSetKeyCallback(mWindow, keyCallBack);
    glfwSetMouseButtonCallback(mWindow, mouseButtonCallBack);
    glfwSetCursorPosCallback(mWindow, cursorPositionCallBack);
    glfwSetScrollCallback(mWindow, scrollCallBack);
    glfwSetWindowUserPointer(mWindow, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

bool Application::update() {
    if (glfwWindowShouldClose(mWindow)) {
        return false;
    }
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
    return true;
}

bool Application::destroy() {
    glfwTerminate();
    return true;
}

int Application::getWidth() {
    return mWidth;
}

int Application::getHeight() {
    return mHeight;
}

Application::~Application() {
}

Application * Application::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new Application();
    }
    return mInstance;
}

Application::Application() {
}

void Application::frameSizeCallback(GLFWwindow *window, int width, int height) {
    Application * self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mFrameBufferSizeCallBack != nullptr) {
        self->mFrameBufferSizeCallBack(width, height);
    }

    // if (Application::getInstance()->mFrameBufferSizeCallBack != nullptr) {
    //     Application::getInstance()->mFrameBufferSizeCallBack(width, height);
    // }
}

void Application::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // std::cout <<"Application :: " << key <<  std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    Application * self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mKeyCallBack != nullptr) {
        self->mKeyCallBack(key, scancode, action, mods);
    }
}

void Application::mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods) {
    Application * self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mMouseButtonCallBack != nullptr) {
        self->mMouseButtonCallBack(button, action, mods);
    }
}

void Application::cursorPositionCallBack(GLFWwindow *window, double xpos, double ypos) {
    Application * self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mCursorPositionCallBack != nullptr) {
        self->mCursorPositionCallBack(xpos, ypos);
    }
}

void Application::scrollCallBack(GLFWwindow *window, double xoffset, double yoffset) {
    Application * self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mScrollCallBack != nullptr) {
        self->mScrollCallBack(xoffset, yoffset);
    }
}

