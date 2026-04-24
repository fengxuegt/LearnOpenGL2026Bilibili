//
// Created by fengxuegt on 2026/3/16.
//

#include "renderer.h"

#include <glframework/material/phongmaterial.h>

#include "glframework/instancedmesh.h"
#include "glframework/material/cubeballmaterial.h"
#include "glframework/material/cubematerial.h"
#include "glframework/material/phongenvmaterial.h"
#include "glframework/material/phonginstancematerial.h"
#include "glframework/material/screenplanematerial.h"
#include "glframework/material/whitematerial.h"
#include "glframework/material/advanced/phongnormalmapmaterial.h"
#include "glframework/material/advanced/phongparallaxmapmaterial.h"

Renderer::Renderer() {
    mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
    mWhiteShader = new Shader("assets/shaders/white.vert", "assets/shaders/white.frag");
    mScreenPlaneShader = new Shader("assets/shaders/screenplane.vert", "assets/shaders/screenplane.frag");
    mCubeShader = new Shader("assets/shaders/cube.vert", "assets/shaders/cube.frag");
    mPhongEnvShader = new Shader("assets/shaders/phongenv.vert", "assets/shaders/phongenv.frag");
    mPhongInstanceShader = new Shader("assets/shaders/phonginstance.vert", "assets/shaders/phonginstance.frag");
    mCubeBallShader = new Shader("assets/shaders/cubeball.vert", "assets/shaders/cubeball.frag");
    mPhongNormalMapShader = new Shader("assets/shaders/advanced/phongnormalmap.vert", "assets/shaders/advanced/phongnormalmap.frag");
    mPhongParallaxMapShader = new Shader("assets/shaders/advanced/phongparallaxmap.vert", "assets/shaders/advanced/phongparallaxmap.frag");
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
    if (object->getType() == ObjectType::Mesh || object->getType() == ObjectType::InstanceMesh) {
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
            case MaterialType::PhongNormalMapMaterial: {
                PhongNormalMapMaterial *phongMaterial = (PhongNormalMapMaterial*)(material);
                // 更新Shader的Uniform变量
                shader->setUniformInt("samplerAsuna", 0);
                shader->setUniformInt("normalMapSampler", 1);
                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());

                shader->setUniformVec3Float("lightDirection", directionalLight->mLightDirection);
                shader->setUniformVec3Float("lightColor", directionalLight->mLightColor);
                shader->setUniformVec3Float("ambientColor", ambientLight->mLightColor);
                shader->setUniformVec3Float("cameraPosition", camera->mPosition);
                shader->setUniformFloat("specularIntensity", directionalLight->mLightIntensity);
                shader->setUniformFloat("mShiness", phongMaterial->mShininess);

                phongMaterial->mDiffuse->Bind();
                phongMaterial->mNormalMap->Bind();
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
                shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(mesh->getModelMatrixAPI())));
            }
            break;
            case MaterialType::PhongParallaxMapMaterial: {
                PhongParallaxMapMaterial *phongMaterial = (PhongParallaxMapMaterial*)(material);
                // 更新Shader的Uniform变量
                shader->setUniformInt("samplerAsuna", 0);
                shader->setUniformInt("normalMapSampler", 1);
                shader->setUniformInt("parallaxMapSampler", 2);

                shader->setUniformMat4("viewMat", camera->getViewMatrix());
                shader->setUniformMat4("projectionMat", camera->getProjectionMatrix());

                shader->setUniformVec3Float("lightDirection", directionalLight->mLightDirection);
                shader->setUniformVec3Float("lightColor", directionalLight->mLightColor);
                shader->setUniformVec3Float("ambientColor", ambientLight->mLightColor);
                shader->setUniformVec3Float("cameraPosition", camera->mPosition);
                shader->setUniformFloat("specularIntensity", directionalLight->mLightIntensity);
                shader->setUniformFloat("mShiness", phongMaterial->mShininess);
                shader->setUniformFloat("heightScale", phongMaterial->mHeightScale);

                phongMaterial->mDiffuse->Bind();
                phongMaterial->mNormalMap->Bind();
                phongMaterial->mParallaxMap->Bind();
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
                phongMaterial->mCubeMap->Bind();
                shader->setUniformMat4("transMat", mesh->getModelMatrixAPI());
                shader->setUniformMat4("normalMat", glm::transpose(glm::inverse(mesh->getModelMatrixAPI())));
            }
            break;
            case MaterialType::PhongInstanceMaterial: {
                PhongInstanceMaterial *phongMaterial = (PhongInstanceMaterial*)(material);
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
            case MaterialType::CubeBallMaterial: {
                CubeBallMaterial *cubeMaterial = (CubeBallMaterial*)(material);
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
        if (object->getType() == ObjectType::InstanceMesh) {
            InstancedMesh *instancedMesh = (InstancedMesh*)object;
            glDrawElementsInstanced(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0, instancedMesh->mInstanceCount);
        } else {
            glDrawElements(GL_TRIANGLES,  geometry->getIndicesCount(), GL_UNSIGNED_INT, NULL);
        }


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
        case MaterialType::PhongInstanceMaterial:
            resultShader = mPhongInstanceShader;
        break;
        case MaterialType::CubeBallMaterial:
            resultShader = mCubeBallShader;
        break;
        case MaterialType::PhongNormalMapMaterial:
            resultShader = mPhongNormalMapShader;
        break;
        case MaterialType::PhongParallaxMapMaterial:
            resultShader = mPhongParallaxMapShader;
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

