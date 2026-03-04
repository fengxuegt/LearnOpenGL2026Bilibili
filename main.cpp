#include<iostream>
#include <shader.h>

#include "core.h"

#include "checkerror.h"
#include "application.h"


void frameSizeCallback(int width, int height) {
    std::cout << width << " " << height << std::endl;
    glViewport(0, 0, width, height);
}

void keyCallBack(int key, int scancode, int action, int mods) {
    std::cout << key << " " << scancode << " " << action << " " << mods << std::endl;
}

GLuint vao;
GLuint program;
Shader *shader = nullptr;
void prepareVAO() {


    float data[] = {
        // 位置              // 颜色
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // 红
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // 绿
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // 蓝
   };
    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    // GLuint aPosLocation =  glGetAttribLocation(program, "aPos");
    // GLuint aColorLocation =  glGetAttribLocation(program, "aColor");
    // 这两个参数可以用于下面的两个API，放到index这个参数的位置；


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glBindVertexArray(0);
}

void prepareShader() {
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 vColor;\n"
        "out vec3 fColor;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   fColor = vColor;\n"
        "}\n";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "in vec3 fColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = vec4(fColor, 1.0f);\n"
        "}\n";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void prepareShaderClass() {
    shader = new Shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
}



int main() {
    if (!LWAPP->init("OpenGL basic", 800, 600)) {
        return -1;
    }
    LWAPP->setFrameBufferSizeCallback(frameSizeCallback);
    LWAPP->setKeyCallBack(keyCallBack);

    LWGLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    prepareVAO();
    prepareShaderClass();
    while (LWAPP->update()) {
        LWGLCALL(glClear(GL_COLOR_BUFFER_BIT));
        shader->useProgram();
        shader->setUniformFloat("time",sin(glfwGetTime()));
        LWGLCALL(glBindVertexArray(vao));
        LWGLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
        shader->unuseProgram();
    }

    LWAPP->destroy();
    return 0;
}
