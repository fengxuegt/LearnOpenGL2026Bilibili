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
#include "gamecameracontrol.h"
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
#include "glframework/material/advanced/phongparallaxmapmaterial.h"

Renderer *renderer;
std::vector<Mesh*> meshes;
Scene *offScene = nullptr;
Scene *onScene = nullptr;
Camera *camera = nullptr;
GameCameraControl *cameraControl = nullptr;
glm::mat4 transMat(1.0f);
glm::mat4 transMatBox(1.0f);
Geometry *plane = nullptr;
Geometry *box = nullptr;
Geometry *sphere = nullptr;
FrameBuffer *fbo = nullptr;

DirectionalLight *dirLight = nullptr;
AmbientLight *ambLight = nullptr;
glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f); // 光的方向
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // 光的颜色
glm::vec3 ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);

PhongParallaxMapMaterial *planeMat = nullptr;

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
    // cameraControl = new TrackBallCameraControl();
    cameraControl = new GameCameraControl();
    cameraControl->setCamera(camera);
    cameraControl->setSensitivity(0.4f);
    cameraControl->setSpeed(0.1f);
}

void prepare() {
    // glEnable(GL_FRAMEBUFFER_SRGB);
    renderer = new Renderer();
    offScene = new Scene();
    onScene = new Scene();
    fbo = new FrameBuffer(LWAPP->getWidth(), LWAPP->getHeight());

    // cube map
    std::vector<std::string> paths = {
        "assets/textures/skybox/right.jpg",
        "assets/textures/skybox/left.jpg",
        "assets/textures/skybox/top.jpg",
        "assets/textures/skybox/bottom.jpg",
        "assets/textures/skybox/back.jpg",
        "assets/textures/skybox/front.jpg",
    };
    auto skyboxGeo = Geometry::createBox(1.0f);
    auto skyboxMat = new CubeMaterial();
    skyboxMat->mDiffuse = new Texture(paths, 0, GL_SRGB_ALPHA);
    auto skyboxMesh = new Mesh(skyboxGeo, skyboxMat);
    offScene->addChild(skyboxMesh);

    // pass 01
    auto planeGeo = Geometry::createNormapPlane();
    planeMat = new PhongParallaxMapMaterial();
    planeMat->mDiffuse = new Texture("assets/textures/parallax/bricks.jpg", 0, GL_SRGB_ALPHA);
    planeMat->mNormalMap = new Texture("assets/textures/parallax/bricks_normal.jpg", 1);
    planeMat->mParallaxMap = new Texture("assets/textures/parallax/disp.jpg", 2);
    planeMat->mShininess = 128;
    auto mesh = new Mesh(planeGeo, planeMat);
    mesh->rotateY(30);
    offScene->addChild(mesh);

    // pass 02
    Geometry * geometry = Geometry::createScreenPlane();
    auto * material = new ScreenPlaneMaterial();
    material->mDiffuse = fbo->mColorAttachment;
    Mesh *plane = new Mesh(geometry, material);
    onScene->addChild(plane);




    // light init
    dirLight = new DirectionalLight();
    dirLight->mLightColor = glm::vec3(1.0f, 1.0f, 1.0f);;
    // dirLight->mLightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
    dirLight->mLightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
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
    ImGui::SliderFloat("heightScale", &planeMat->mHeightScale, 0.0f, 1.0f);
    // ImGui::ColorEdit3("Clear", (float*)&dirLight->mLightColor);
    ImGui::End();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(LWAPP->getWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

int main() {
    if (!LWAPP->init("OpenGL basic", 2560, 1440)) {
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
    glViewport(0, 0, 2560, 1440);
    while (LWAPP->update()) {
        cameraControl->update();
        renderer->render(offScene, camera, dirLight, ambLight, fbo->mFbo);
        renderer->render(onScene, camera, dirLight, ambLight, 0);
        renderIMGUI();
    }

    LWAPP->destroy();
    return 0;
}