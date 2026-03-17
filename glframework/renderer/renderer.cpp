//
// Created by fengxuegt on 2026/3/16.
//

#include "renderer.h"

#include <glframework/material/phongmaterial.h>

Renderer::Renderer() {
    mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
}

Renderer::~Renderer() {
}

void Renderer::render(const std::vector<Mesh *> &meshes, Camera *camera, DirectionalLight *directionalLight,
    AmbientLight *ambientLight) {

    // 设置OpenGL 状态机参数
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // 清理画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            default:
                continue;
        }
        glBindVertexArray(geometry->getVao());
        glDrawElements(GL_TRIANGLES,  geometry->getIndicesCount(), GL_UNSIGNED_INT, NULL);

        shader->unuseProgram();

    }
}

Shader * Renderer::pickShader(MaterialType type) {
    Shader *resultShader = nullptr;
    switch (type) {
        case MaterialType::PhongMaterial:
            //
                resultShader = mPhongShader;
                break;
        default:
            break;
    }
    return resultShader;
}

