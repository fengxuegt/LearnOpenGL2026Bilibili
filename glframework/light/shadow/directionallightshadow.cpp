//
// Created by fengxuegt on 2026/5/11.
//

#include "directionallightshadow.h"

#include <orthographiccamera.h>

DirectionalLightShadow::DirectionalLightShadow() {
    float size = 10.0f;
    mCamera = new OrthographicCamera(-size, size, -size, size, 0.1f, 80.0f);
    mRenderTarget = FrameBuffer::createShadowFbo(2048, 2048);

}

DirectionalLightShadow::~DirectionalLightShadow() {
    delete mCamera;
    delete mRenderTarget;
}

void DirectionalLightShadow::sentRenderTargetSize(int width, int height) {
     if (mRenderTarget != nullptr) {
         delete mRenderTarget;
     }
    mRenderTarget = FrameBuffer::createShadowFbo(width, height);
}

glm::mat4 DirectionalLightShadow::getLightMatrix(glm::mat4 lightModelMatrix) {
    auto viewMatrix = glm::inverse(lightModelMatrix);
    auto projectionMatrix = mCamera->getProjectionMatrix();
    return projectionMatrix * viewMatrix;
}
