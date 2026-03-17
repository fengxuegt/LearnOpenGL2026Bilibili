#include<iostream>
#include <shader.h>

#include "core.h"

#include "checkerror.h"
#include "application.h"
#define STB_IMAGE_IMPLEMENTATION
#include <camera.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glframework/material/phongmaterial.h>
#include <glframework/renderer/renderer.h>

#include "cameracontrol.h"
#include "geometry.h"
#include "perspectivecamera.h"
#include "stb_image.h"
#include "texture.h"
#include "trackballcameracontrol.h"

Renderer *renderer;
std::vector<Mesh*> meshes;
Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;
glm::mat4 transMat(1.0f);
glm::mat4 transMatBox(1.0f);
Geometry *plane = nullptr;
Geometry *box = nullptr;
Geometry *sphere = nullptr;

DirectionalLight *dirLight = nullptr;
AmbientLight *ambLight = nullptr;
glm::vec3 lightDirection = glm::vec3(-1.0f, -1.0f, -1.0f); // 光的方向
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // 光的颜色
glm::vec3 ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);

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

void prepareTexture() {
    texture = new Texture("assets/textures/asuna.png", 0);
    boxTexture = new Texture("assets/textures/box.png", 0);
}
void prepareShaderClass() {
    shader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
}
void prepareCamera() {
    camera = new PerspectiveCamera(60.0f, (float)LWAPP->getWidth()/ (float)LWAPP->getHeight(), 0.1f, 1000.0f);
    cameraControl = new TrackBallCameraControl();
    cameraControl->setCamera(camera);
}
void prepareState (){
    LWGLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    glEnable(GL_DEPTH_TEST);
}
void prepareMesh() {
    plane = Geometry::createPlane(3, 3);
    box = Geometry::createBox(3);
    sphere = Geometry::createSphere(1);
}
void render() {
    LWGLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    shader->useProgram();
    shader->setUniformInt("samplerAsuna", 0);
    shader->setUniformMat4("viewMat", camera->getViewMatrix());
    shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());

    shader->setUniformVec3Float("lightDirection", lightDirection);
    shader->setUniformVec3Float("lightColor", lightColor);
    shader->setUniformVec3Float("ambientColor", ambientColor);
    shader->setUniformVec3Float("cameraPosition", camera->mPosition);
    shader->setUniformFloat("specularIntensity", 8.0f);

    texture->Bind();
    transMatBox = glm::mat4(1.0f);
    transMatBox = glm::translate(transMatBox, glm::vec3(3.0f, 0.5f, 1.0f));
    transMatBox = glm::rotate(transMatBox, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.0f, 1.0f, 0.0f));
    shader->setUniformMat4("transMat", transMatBox);
    shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(transMatBox)));
    LWGLCALL(glBindVertexArray(sphere->getVao()));
    LWGLCALL(glDrawElements(GL_TRIANGLES,  sphere->getIndicesCount(), GL_UNSIGNED_INT, NULL));

    texture->Bind();
    transMat = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 100), glm::vec3(0.0f, 1.0f, 0.0f));
    shader->setUniformMat4("transMat", transMat);
    shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(transMat)));
    LWGLCALL(glBindVertexArray(box->getVao()));
    LWGLCALL(glDrawElements(GL_TRIANGLES,  box->getIndicesCount(), GL_UNSIGNED_INT, NULL));

    shader->unuseProgram();
}
void prepare() {
    renderer = new Renderer();

    // first mesh
    Mesh *boxMesh = new Mesh();
    box = Geometry::createBox(2);
    boxMesh->mGeometry = box;
    auto *boxMaterial = new PhongMaterial();
    boxMaterial->mDiffuse =  new Texture("assets/textures/asuna.png", 0);
    boxMaterial->mShininess = 64.0f;
    boxMesh->mMaterial = boxMaterial;
    boxMesh->setPosition(glm::vec3(0.0, 0, 0));
    meshes.push_back(boxMesh);

    // light init
    dirLight = new DirectionalLight();
    dirLight->mLightColor = lightColor;
    dirLight->mLightDirection = lightDirection;
    dirLight->mLightIntensity = 0.5f;
    ambLight = new AmbientLight();
    ambLight->mLightColor = lightColor;

    // second mesh
    Mesh *sphereMesh = new Mesh();
    sphere = Geometry::createSphere(1);
    sphereMesh->mGeometry = sphere;
    auto *sphereMaterial = new PhongMaterial();
    sphereMaterial->mDiffuse = new Texture("assets/textures/box.png", 0);
    sphereMaterial->mShininess = 64.0f;
    sphereMesh->mMaterial = sphereMaterial;
    sphereMesh->setPosition(glm::vec3(4.0, 0.0, 0.0));
    meshes.push_back(sphereMesh);
    plane = Geometry::createPlane(3, 3);
}

void initIMGUI() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(LWAPP->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

}
void renderIMGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello world");
    ImGui::Text("Hello World");
    ImGui::Button("Test Button", ImVec2(20, 20));
    ImGui::ColorEdit3("Clear", (float*)&dirLight->mLightColor);
    ImGui::End();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(LWAPP->getWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

    // prepareState();
    // prepareMesh();
    // prepareShaderClass();
    // prepareTexture();
    initIMGUI();

    prepareCamera();
    prepare();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (LWAPP->update()) {
        meshes[1]->rotateY(0.3);
        meshes[1]->rotateX(0.8);
        cameraControl->update();
        renderer->render(meshes, camera, dirLight, ambLight);
        renderIMGUI();
    }

    LWAPP->destroy();
    return 0;
}