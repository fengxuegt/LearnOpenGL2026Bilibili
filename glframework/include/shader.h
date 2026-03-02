//
// Created by fengxuegt on 2026/3/2.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>

#include "core.h"


class Shader {
public:
    bool setUniformInt(const std::string& name, int value);
public:
    void useProgram();
    void unuseProgram();
    Shader();
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();


private:
    GLuint mProgram;
    void checkCompileErrors(GLuint object, GLuint type);
    std::string readFromFile(const std::string & path);

};



#endif //SHADER_H
