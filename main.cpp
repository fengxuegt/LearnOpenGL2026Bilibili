#include<iostream>
#include <shader.h>

#include "core.h"

#include "checkerror.h"
#include "application.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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


   //  float data[] = {
   //      // 位置              // 颜色
   //      0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 0.5f, 1.0f, // 红
   //     -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,// 绿
   //      0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f, 0.0f   // 蓝
   //
   // };
    float data [] = {
         -1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 左上
        1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,// 右上
         -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f , // 左下
        1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f, 0.0f   // 右下
         };
    unsigned int ebos[] = {
        0, 1, 2,
        1, 3, 2,
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

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebos), ebos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
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
GLuint textureID;
void prepareTexture() {
    int width, height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    auto image_data = stbi_load("assets/textures/asuna.png", &width, &height, &channels, STBI_rgb_alpha); // unsigned char * data
    // auto image_data = stbi_load("assets/textures/box.png", &width, &height, &channels, STBI_rgb_alpha); // unsigned char * data

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
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
    prepareTexture();
    while (LWAPP->update()) {
        LWGLCALL(glClear(GL_COLOR_BUFFER_BIT));
        shader->useProgram();
        shader->setUniformFloat("time",sin(glfwGetTime()));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        shader->setUniformInt("samplerAsuna", 0);
        LWGLCALL(glBindVertexArray(vao));
        // LWGLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
        LWGLCALL(glDrawElements(GL_TRIANGLES,  6, GL_UNSIGNED_INT, NULL));
        shader->unuseProgram();
    }

    LWAPP->destroy();
    return 0;
}