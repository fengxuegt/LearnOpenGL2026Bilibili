#include<iostream>
#include <shader.h>

#include "core.h"

#include "checkerror.h"
#include "application.h"
#define STB_IMAGE_IMPLEMENTATION
#include <assimpLoader.h>
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
#include "glframework/material/whitematerial.h"

Renderer *renderer;
std::vector<Mesh*> meshes;
Scene *scene = nullptr;
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

Shader *shader = nullptr;
Texture *texture = nullptr;
Texture *boxTexture = nullptr;

void prepareCamera() {
    camera = new PerspectiveCamera(60.0f, (float)LWAPP->getWidth()/ (float)LWAPP->getHeight(), 0.1f, 1000.0f);
    cameraControl = new TrackBallCameraControl();
    cameraControl->setCamera(camera);
}

void prepare() {
    renderer = new Renderer();
    scene = new Scene();

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

    // boxMesh->addChild(sphereMesh);
    plane = Geometry::createPlane(3, 3);

    scene->addChild(boxMesh);


    // scene->addChild(sphereMesh);
}

void prepareStencilTest() {
    renderer = new Renderer();
    scene = new Scene();

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

    Mesh *outBoxMesh = new Mesh();
    outBoxMesh->mGeometry = box;
    outBoxMesh->mMaterial = new WhiteMaterial();
    outBoxMesh->setPosition(boxMesh->getPosition());
    outBoxMesh->setScale(glm::vec3(1.2f, 1.2f, 1.2f));
    // light init
    dirLight = new DirectionalLight();
    dirLight->mLightColor = lightColor;
    dirLight->mLightDirection = lightDirection;
    dirLight->mLightIntensity = 0.5f;
    ambLight = new AmbientLight();
    ambLight->mLightColor = lightColor;

    // scene->addChild(boxMesh);
    // scene->addChild(outBoxMesh);
    // meshes.push_back(boxMesh);
    meshes.push_back(outBoxMesh);

    Mesh *secondBoxMesh = new Mesh();
    secondBoxMesh->mGeometry = box;
    secondBoxMesh->setPosition(boxMesh->getPosition() + glm::vec3(0.5, 0.5, 0));
    secondBoxMesh->mMaterial = boxMaterial;
    // meshes.push_back(secondBoxMesh);

    Mesh *outSecondBoxMesh = new Mesh();
    outSecondBoxMesh->mGeometry = box;
    outSecondBoxMesh->setPosition(boxMesh->getPosition() + glm::vec3(0.5, 0.5, 0));
    outSecondBoxMesh->mMaterial = new WhiteMaterial();
    outSecondBoxMesh->setScale(glm::vec3(1.2f, 1.2f, 1.2f));
    // meshes.push_back(outSecondBoxMesh);

}
void prepareFBX() {
    renderer = new Renderer();
    scene = new Scene();
    auto testModel = AssimpLoader::load("assets/fbx/Fist Fight B.fbx");
    // testModel->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
    scene->addChild(testModel);

    dirLight = new DirectionalLight();
    dirLight->mLightColor = lightColor;
    dirLight->mLightDirection = lightDirection;
    dirLight->mLightIntensity = 0.5f;
    ambLight = new AmbientLight();
    ambLight->mLightColor = lightColor;
    ambLight->mLightIntensity = 0.5f;


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

    scene->addChild(sphereMesh);
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
    // prepareFBX();
    prepareStencilTest();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (LWAPP->update()) {
        cameraControl->update();
        // renderer->render(scene, camera, dirLight, ambLight);
        renderIMGUI();
        renderer->render(meshes, camera, dirLight, ambLight);
    }

    LWAPP->destroy();
    return 0;
}