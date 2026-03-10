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
    bool setUniformFloat(const std::string& name, float value);
    bool setUniformVec3Int(const std::string name, float v0, float v1, float v2);
    bool setUniformMat4(const std::string& name, const glm::mat4& matrix);
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
