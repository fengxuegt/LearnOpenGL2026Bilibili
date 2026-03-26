//
// Created by fengxuegt on 2026/3/16.
//

#include "renderer.h"

#include <glframework/material/phongmaterial.h>

#include "glframework/material/whitematerial.h"

Renderer::Renderer() {
    mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
    mWhiteShader = new Shader("assets/shaders/white.vert", "assets/shaders/white.frag");
}

Renderer::~Renderer() {
}

void Renderer::render(const std::vector<Mesh *> &meshes, Camera *camera, DirectionalLight *directionalLight,
    AmbientLight *ambientLight) {

    // 设置OpenGL 状态机参数
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0XFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // glStencilFunc(GL_LESS, 1, 0xFF);

    // 清理画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

    // 遍历mesh列表
    for (int i = 0; i < meshes.size(); i++) {

        if (i == 0) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glStencilMask(0XFF);
        } else if (i == 1) {
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0X00);
        }


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
            default:
                continue;
        }
        glBindVertexArray(geometry->getVao());
        glDrawElements(GL_TRIANGLES,  geometry->getIndicesCount(), GL_UNSIGNED_INT, NULL);

        shader->unuseProgram();

    }
}

void Renderer::render(Scene *scene, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderObject(scene, camera, directionalLight, ambientLight);
}

void Renderer::renderObject(Object *object, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight) {
    if (object->getType() == ObjectType::Mesh) {
        Mesh *mesh = (Mesh*)object;
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
        default:
            break;
    }
    return resultShader;
}

