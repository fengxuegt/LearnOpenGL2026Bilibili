//
// Created by fengxuegt on 2026/3/16.
//

#include "directionallight.h"

#include "shadow/directionallightshadow.h"

DirectionalLight::DirectionalLight() {
    mShadow = new DirectionalLightShadow();
}

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction) {
    mLightColor = color;
    mShadow = new DirectionalLightShadow();
}

DirectionalLight::~DirectionalLight() {
}
