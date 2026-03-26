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


class Renderer {
public:
    Renderer();
    ~Renderer();
    void render(const std::vector<Mesh*> &meshes, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight);
    void render(Scene * scene, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight, int fbo = 0);
    void renderObject(Object *object, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight);
private:
    Shader* pickShader(MaterialType type);

private:
    std::vector<Mesh*> mMeshes;
    Shader *mPhongShader{nullptr};
    Shader *mWhiteShader{nullptr};
    Shader *mScreenPlaneShader{nullptr};
};



#endif //RENDERER_H
