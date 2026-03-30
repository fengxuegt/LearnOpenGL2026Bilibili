//
// Created by fengxuegt on 2026/3/16.
//

#include "renderer.h"

#include <glframework/material/phongmaterial.h>

#include "glframework/material/cubematerial.h"
#include "glframework/material/phongenvmaterial.h"
#include "glframework/material/screenplanematerial.h"
#include "glframework/material/whitematerial.h"

Renderer::Renderer() {
    mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
    mWhiteShader = new Shader("assets/shaders/white.vert", "assets/shaders/white.frag");
    mScreenPlaneShader = new Shader("assets/shaders/screenplane.vert", "assets/shaders/screenplane.frag");
    mCubeShader = new Shader("assets/shaders/cube.vert", "assets/shaders/cube.frag");
    mPhongEnvShader = new Shader("assets/shaders/phongenv.vert", "assets/shaders/phongenv.frag");
}

Renderer::~Renderer() {
}

void Renderer::render(const std::vector<Mesh *> &meshes, Camera *camera, DirectionalLight *directionalLight,
    AmbientLight *ambientLight) {
    // 清理画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // 遍历mesh列表
    for (int i = 0; i < meshes.size(); i++) {
        auto mesh = meshes[i];
        auto geometry = mesh->mGeometry;
        auto material = mesh->mMaterial;
        Shader *shader = pickShader(material->getType());
        shader->useProgram();

        switch (material->getType()) {
            case MaterialType::PhongMaterial: {
                PhongMaterial *phongMaterial = (PhongMaterial*)(material);
                // 更新Shader的Uniform变量
                shader->setUniformInt("samplerAsuna", 0);
                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());

                shader->setUniformVec3Float("lightDirection", directionalLight->mLightDirection);
                shader->setUniformVec3Float("lightColor", directionalLight->mLightColor);
                shader->setUniformVec3Float("ambientColor", ambientLight->mLightColor);
                shader->setUniformVec3Float("cameraPosition", camera->mPosition);
                shader->setUniformFloat("specularIntensity", directionalLight->mLightIntensity);
                shader->setUniformFloat("mShiness", phongMaterial->mShininess);

                phongMaterial->mDiffuse->Bind();
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
                shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(mesh->getModelMatrixAPI())));
            }
                break;
            case MaterialType::WhiteMaterial: {
                WhiteMaterial *whiteMaterial = (WhiteMaterial*)(material);
                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
            }
            break;
            case MaterialType::ScreenPlaneMaterial: {
                ScreenPlaneMaterial *screenPlaneMaterial = (ScreenPlaneMaterial*)(material);
                screenPlaneMaterial->mDiffuse->Bind();
                shader->setUniformInt("diffuse", 0);
            }
            break;
            default:
                continue;
        }
        glBindVertexArray(geometry->getVao());
        glDrawElements(GL_TRIANGLES,  geometry->getIndicesCount(), GL_UNSIGNED_INT, NULL);

        shader->unuseProgram();

    }
}

void Renderer::render(Scene *scene, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight, int fbo) {
    if (fbo) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderObject(scene, camera, directionalLight, ambientLight);
}

void Renderer::renderObject(Object *object, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight) {
    if (object->getType() == ObjectType::Mesh) {
        Mesh *mesh = (Mesh*)object;
        auto geometry = mesh->mGeometry;
        auto material = mesh->mMaterial;

        setDepthState(material);


        Shader *shader = pickShader(material->getType());
        shader->useProgram();

        switch (material->getType()) {
            case MaterialType::PhongMaterial: {
                    PhongMaterial *phongMaterial = (PhongMaterial*)(material);
                    // 更新Shader的Uniform变量
                    shader->setUniformInt("samplerAsuna", 0);
                    shader->setUniformMat4("viewMat", camera->getViewMatrix());
                    shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());

                    shader->setUniformVec3Float("lightDirection", directionalLight->mLightDirection);
                    shader->setUniformVec3Float("lightColor", directionalLight->mLightColor);
                    shader->setUniformVec3Float("ambientColor", ambientLight->mLightColor);
                    shader->setUniformVec3Float("cameraPosition", camera->mPosition);
                    shader->setUniformFloat("specularIntensity", directionalLight->mLightIntensity);
                    shader->setUniformFloat("mShiness", phongMaterial->mShininess);

                    phongMaterial->mDiffuse->Bind();
                    shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
                    shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(mesh->getModelMatrixAPI())));
                }
                break;
            case MaterialType::PhongEnvMaterial: {
                PhongEnvMaterial *phongMaterial = (PhongEnvMaterial*)(material);
                // 更新Shader的Uniform变量
                shader->setUniformInt("cubeSampler", 1);
                shader->setUniformInt("samplerAsuna", 0);
                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());

                shader->setUniformVec3Float("lightDirection", directionalLight->mLightDirection);
                shader->setUniformVec3Float("lightColor", directionalLight->mLightColor);
                shader->setUniformVec3Float("ambientColor", ambientLight->mLightColor);
                shader->setUniformVec3Float("cameraPosition", camera->mPosition);
                shader->setUniformFloat("specularIntensity", directionalLight->mLightIntensity);
                shader->setUniformFloat("mShiness", phongMaterial->mShininess);

                phongMaterial->mDiffuse->Bind();
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
                shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(mesh->getModelMatrixAPI())));
            }
            break;
            case MaterialType::WhiteMaterial: {
                WhiteMaterial *whiteMaterial = (WhiteMaterial*)(material);
                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());

            }
                break;
            case MaterialType::ScreenPlaneMaterial: {
                ScreenPlaneMaterial *screenPlaneMaterial = (ScreenPlaneMaterial*)(material);
                screenPlaneMaterial->mDiffuse->Bind();
                shader->setUniformInt("diffuse", 0);
            }
                break;
            case MaterialType::CubeMaterial: {
                CubeMaterial *cubeMaterial = (CubeMaterial*)(material);
                mesh->setPosition(camera->mPosition);
                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
                shader->setUniformInt("diffuse", 0);
                cubeMaterial->mDiffuse->Bind();
            }
                break;
            default:
                break;
        }
        glBindVertexArray(geometry->getVao());
        glDrawElements(GL_TRIANGLES,  geometry->getIndicesCount(), GL_UNSIGNED_INT, NULL);

        shader->unuseProgram();
    }
    auto children = object->getChildren();
    for (int i = 0; i < children.size(); i++) {
        renderObject(children[i], camera, directionalLight, ambientLight);
    }
}

Shader * Renderer::pickShader(MaterialType type) {
    Shader *resultShader = nullptr;
    switch (type) {
        case MaterialType::PhongMaterial:
            //
                resultShader = mPhongShader;
                break;
        case MaterialType::WhiteMaterial:
            resultShader = mWhiteShader;
            break;
        case MaterialType::ScreenPlaneMaterial:
            resultShader = mScreenPlaneShader;
            break;
        case MaterialType::CubeMaterial:
            resultShader = mCubeShader;
            break;
        case MaterialType::PhongEnvMaterial:
            resultShader = mPhongEnvShader;
            break;
        default:
            break;
    }
    return resultShader;
}

void Renderer::setDepthState(Material *material) {
    if (material->mDepthTest) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(material->mDepthFun);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    if (material->mDepthWrite) {
        glDepthMask(GL_TRUE);
    } else {
        glDepthMask(GL_FALSE);
    }

}

