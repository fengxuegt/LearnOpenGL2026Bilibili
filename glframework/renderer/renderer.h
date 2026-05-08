//
// Created by fengxuegt on 2026/3/16.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <mesh.h>
#include "core.h"
#include <vector>
#include <camera.h>
#include <shader.h>
#include <../light/ambientlight.h>
#include <../light/directionallight.h>

#include "scene.h"
#include "glframework/framebuffer.h"


class Renderer {
public:
    Renderer();
    ~Renderer();
    void render(const std::vector<Mesh*> &meshes, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight);
    void render(Scene * scene, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight, int fbo = 0);
    void renderObject(Object *object, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight);

    void renderShadowMap(const std::vector<Mesh*> &meshes, DirectionalLight *directionalLight, FrameBuffer *fbo);
    glm::mat4 getLightMatrix(DirectionalLight *directional_light);

private:
    Shader* pickShader(MaterialType type);
    void setDepthState(Material *material);
    void projectObject(Object* obj);


private:
    std::vector<Mesh*> mMeshes;
    Shader *mPhongShader{nullptr};
    Shader *mWhiteShader{nullptr};
    Shader *mScreenPlaneShader{nullptr};
    Shader *mCubeShader{nullptr};
    Shader *mPhongEnvShader{nullptr};
    Shader *mPhongInstanceShader{nullptr};
    Shader *mCubeBallShader{nullptr};
    Shader *mPhongNormalMapShader{nullptr};
    Shader *mPhongParallaxMapShader{nullptr};
    Shader *mPhongShadowMapShader{nullptr};
    Shader *mShadowShader{nullptr};
public:
    std::vector<Mesh*> mOpacityObjects{};
    FrameBuffer *mShadowFBO{nullptr};


};



#endif //RENDERER_H
