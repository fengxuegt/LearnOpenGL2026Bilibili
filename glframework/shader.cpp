//
// Created by fengxuegt on 2026/3/2.
//

#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

bool Shader::setUniformInt(const std::string &name, int value) {
    GLuint location = glGetUniformLocation(mProgram, name.c_str());
    glUniform1i(location, value);
    return true;
}

bool Shader::setUniformFloat(const std::string &name, float value) {
    GLuint location = glGetUniformLocation(mProgram, name.c_str());
    glUniform1f(location, value);
    return true;
}

bool Shader::setUniformVec3Int(const std::string name, float v0, float v1, float v2) {
    GLuint location = glGetUniformLocation(mProgram, name.c_str());
    glUniform3i(location, v0, v1, v2);
    return true;
}

bool Shader::setUniformVec3Float(const std::string name, glm::vec3 vec) {
    GLuint location = glGetUniformLocation(mProgram, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vec));
    return true;
}

bool Shader::setUniformMat4(const std::string &name, const glm::mat4 &matrix) {
    GLuint location = glGetUniformLocation(mProgram, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    return true;
}

void Shader::useProgram() {
    glUseProgram(mProgram);
}

void Shader::unuseProgram() {
    glUseProgram(0);
}

Shader::Shader() {
    mProgram = 0;

}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::string vertexSource   = readFromFile(vertexShaderPath);
    std::string fragmentSource = readFromFile(fragmentShaderPath);

    const char* vCode = vertexSource.c_str();
    const char* fCode = fragmentSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, GL_COMPILE_STATUS);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, GL_COMPILE_STATUS);
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);
    checkCompileErrors(mProgram, GL_LINK_STATUS);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}



Shader::~Shader() {
    if (mProgram != 0) {
        glDeleteProgram(mProgram);
    }
}

void Shader::checkCompileErrors(GLuint object, GLuint type) {
    int success;
    switch (type) {
        case GL_COMPILE_STATUS:
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(object, 512, NULL, infoLog);
                std::cout << infoLog << std::endl;
            }
            break;
        case GL_LINK_STATUS:
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(object, 512, NULL, infoLog);
                std::cout << infoLog << std::endl;
            }
            break;
        default:
            std::cout << "Unknown shader type: " << type << std::endl;
            break;
    }
}

std::string Shader::readFromFile(const std::string & path) {

        // 1️⃣ 打开文件（RAII）
        std::ifstream file(path, std::ios::in | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + path);
        }

        // 2️⃣ 读取整个文件到 stringstream
        std::ostringstream ss;
        ss << file.rdbuf();

        // 3️⃣ 自动关闭文件（析构时）
        return ss.str();

}
