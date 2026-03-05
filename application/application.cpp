//
// Created by fengxuegt on 2026/2/27.
//

#include "application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Application::init(const char* title, int width, int height) {
    mWidth = width;
    mHeight = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    mWindow = glfwCreateWindow(640, 480, title, NULL, NULL);
    if (!mWindow) {
        return false;
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, frameSizeCallback);
    glfwSetKeyCallback(mWindow, keyCallBack);
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
