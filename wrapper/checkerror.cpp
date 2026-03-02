//
// Created by fengxuegt on 2026/2/26.
//


#include <string>
#include "./include/checkerror.h"

#include <iostream>
#include <glad/glad.h>


void checkError() {
    std::string errorMsg = "";
    GLenum errorNo = glGetError();
    if (errorNo != GL_NO_ERROR) {
        switch (errorNo) {
            case GL_INVALID_ENUM:
                errorMsg = "GL_INVALID_ENUM";
            break;
            case GL_INVALID_OPERATION:
                errorMsg = "GL_INVALID_OPERATION";
            break;
            case GL_OUT_OF_MEMORY:
                errorMsg = "GL_OUT_OF_MEMORY";
            break;
            default:
                errorMsg = "Unknown error";
            break;
        }
        std::cout << errorMsg << std::endl;
    }
}
