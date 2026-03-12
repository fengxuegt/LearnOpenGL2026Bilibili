#include<iostream>
#include <shader.h>

#include "core.h"

#include "checkerror.h"
#include "application.h"
#define STB_IMAGE_IMPLEMENTATION
#include <camera.h>

#include "cameracontrol.h"
#include "geometry.h"
#include "perspectivecamera.h"
#include "stb_image.h"
#include "texture.h"
#include "trackballcameracontrol.h"

Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;
glm::mat4 transMat(1.0f);
glm::mat4 transMatBox(1.0f);
Geometry *plane = nullptr;
Geometry *box = nullptr;
Geometry *sphere = nullptr;

void frameSizeCallback(int width, int height) {
    std::cout << width << " " << height << std::endl;
    glViewport(0, 0, width, height);
}

void keyCallBack(int key, int scancode, int action, int mods) {
    std::cout << key << " " << scancode << " " << action << " " << mods << std::endl;
    cameraControl->onKey(key, action, mods);
}

void mouseButtonCallBack(int button, int action, int mods) {
    double x, y;
    LWAPP->getCurrentXYPosition(&x, &y);
    cameraControl->onMouse(button, action, x, y);
}

void cursorPositionCallBack(double xpos, double ypos) {
    cameraControl->onCursor(xpos, ypos);
}

void scrollCallback(double xoffset, double yoffset) {
    cameraControl->onScroll(yoffset);
}

GLuint asunavao, boxvao;
GLuint program;
Shader *shader = nullptr;
Texture *texture = nullptr;
Texture *boxTexture = nullptr;

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
    glGenVertexArrays(1, &asunavao);
    glBindVertexArray(asunavao);
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
void prepareTexture() {
    texture = new Texture("assets/textures/asuna.png", 0);
    boxTexture = new Texture("assets/textures/box.png", 0);
}
void prepareShaderClass() {
    shader = new Shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
}
void prepareCamera() {
    camera = new PerspectiveCamera(60.0f, (float)LWAPP->getWidth()/ (float)LWAPP->getHeight(), 0.1f, 1000.0f);
    cameraControl = new TrackBallCameraControl();
    cameraControl->setCamera(camera);
}
void prepareState (){
    glEnable(GL_DEPTH_TEST);
}
void prepareMesh() {
    plane = Geometry::createPlane(3, 3);
    box = Geometry::createBox(3);
    sphere = Geometry::createSphere(1);
}

int main() {
    if (!LWAPP->init("OpenGL basic", 800, 600)) {
        return -1;
    }
    LWAPP->setFrameBufferSizeCallback(frameSizeCallback);
    LWAPP->setKeyCallBack(keyCallBack);
    LWAPP->setMouseButtonCallBack(mouseButtonCallBack);
    LWAPP->setCursorPositionCallBack(cursorPositionCallBack);
    LWAPP->setScrollCallBack(scrollCallback);

    LWGLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    prepareState();
    prepareMesh();
    prepareShaderClass();
    prepareTexture();
    prepareCamera();
    while (LWAPP->update()) {
        cameraControl->update();
        LWGLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        shader->useProgram();
        shader->setUniformInt("samplerAsuna", 0);
        shader->setUniformFloat("time",sin(glfwGetTime()));
        shader->setUniformMat4("viewMat", camera->getViewMatrix());
        shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());
        texture->Bind();
        transMatBox = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.5f, 1.0f));
        shader->setUniformMat4("transMat", transMatBox);
        LWGLCALL(glBindVertexArray(sphere->getVao()));
        LWGLCALL(glDrawElements(GL_TRIANGLES,  sphere->getIndicesCount(), GL_UNSIGNED_INT, NULL));

        texture->Bind();
        shader->setUniformMat4("transMat", transMat);
        LWGLCALL(glBindVertexArray(box->getVao()));
        LWGLCALL(glDrawElements(GL_TRIANGLES,  box->getIndicesCount(), GL_UNSIGNED_INT, NULL));


        shader->unuseProgram();
    }

    LWAPP->destroy();
    return 0;
}