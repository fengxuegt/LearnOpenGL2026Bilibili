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
#include "glframework/framebuffer.h"
#include "glframework/instancedmesh.h"
#include "glframework/material/cubeballmaterial.h"
#include "glframework/material/cubematerial.h"
#include "glframework/material/phongenvmaterial.h"
#include "glframework/material/phonginstancematerial.h"
#include "glframework/material/screenplanematerial.h"
#include "glframework/material/whitematerial.h"
#include "glframework/material/advanced/phongnormalmapmaterial.h"

Renderer *renderer;
std::vector<Mesh*> meshes;
Scene *offScene = nullptr;
Scene *onScene = nullptr;
Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;
glm::mat4 transMat(1.0f);
glm::mat4 transMatBox(1.0f);
Geometry *plane = nullptr;
Geometry *box = nullptr;
Geometry *sphere = nullptr;
FrameBuffer *fbo = nullptr;

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
    // glEnable(GL_FRAMEBUFFER_SRGB);
    renderer = new Renderer();
    offScene = new Scene();
    onScene = new Scene();
    fbo = new FrameBuffer(LWAPP->getWidth(), LWAPP->getHeight());

    // pass 01
    auto boxGeo = Geometry::createBox(5.0f);
    auto boxMat = new PhongMaterial();
    boxMat->mDiffuse = new Texture("assets/textures/parallax/bricks.jpg", 0, GL_SRGB_ALPHA);
    auto boxMesh = new Mesh(boxGeo, boxMat);
    offScene->addChild(boxMesh);

    // pass 02
    Geometry * geometry = Geometry::createScreenPlane();
    auto * material = new ScreenPlaneMaterial();
    material->mDiffuse = fbo->mColorAttachment;
    Mesh *plane = new Mesh(geometry, material);
    onScene->addChild(plane);

    std::vector<std::string> paths = {
        "assets/textures/skybox/right.jpg",
        "assets/textures/skybox/left.jpg",
        "assets/textures/skybox/top.jpg",
        "assets/textures/skybox/bottom.jpg",
        "assets/textures/skybox/back.jpg",
        "assets/textures/skybox/front.jpg",
    };


    /*
    // cube map
    Mesh *boxMesh = new Mesh();
    box = Geometry::createBox(1);
    boxMesh->mGeometry = box;
    auto *boxMaterial = new CubeMaterial();
    // auto *boxMaterial = new CubeBallMaterial();
    // boxMaterial->mDiffuse = new Texture("assets/textures/bk.jpg", 0);
    boxMaterial->mDiffuse = new Texture(paths, 0);
    boxMesh->mMaterial = boxMaterial;
    boxMesh->setPosition(glm::vec3(0.0, 0, 0));


    offScene->addChild(boxMesh);


    Geometry *normalMapPlane = Geometry::createPlane(5, 3);
    auto * phongMat = new PhongMaterial();
    phongMat->mShininess = 64;
    phongMat->mDiffuse = new Texture("assets/textures/parallax/bricks.jpg", 0);

    auto *normalMapMat = new PhongNormalMapMaterial();
    normalMapMat->mShininess = 128;
    normalMapMat->mDiffuse = new Texture("assets/textures/parallax/bricks.jpg", 0);
    normalMapMat->mNormalMap = new Texture("assets/textures/parallax/bricks_normal.jpg", 1);

    auto *parallaxMapMat = new PhongNormalMapMaterial();
    parallaxMapMat->mShininess = 128;
    parallaxMapMat->mDiffuse = new Texture("assets/textures/parallax/bricks.jpg", 0);
    parallaxMapMat->mNormalMap = new Texture("assets/textures/parallax/bricks_normal.jpg", 1);

    // Mesh *planeMesh = new Mesh(normalMapPlane, normalMapMat);
    Mesh *planeMesh = new Mesh(normalMapPlane, parallaxMapMat);
    // Mesh *planeMesh = new Mesh(normalMapPlane, phongMat);
    planeMesh->setPosition(glm::vec3(0, 0, 2));
    planeMesh->setAngleY(30);
    offScene->addChild(planeMesh);
    */

    // light init
    dirLight = new DirectionalLight();
    dirLight->mLightColor = lightColor;
    dirLight->mLightDirection = lightDirection;
    dirLight->mLightIntensity = 0.5f;
    ambLight = new AmbientLight();
    ambLight->mLightColor = lightColor;

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
    // ImGui::ColorEdit3("Clear", (float*)&dirLight->mLightColor);
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

    initIMGUI();
    prepare();
    prepareCamera();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (LWAPP->update()) {
        cameraControl->update();
        renderer->render(offScene, camera, dirLight, ambLight, fbo->mFbo);
        renderIMGUI();
        renderer->render(onScene, camera, dirLight, ambLight, 0);
    }

    LWAPP->destroy();
    return 0;
}