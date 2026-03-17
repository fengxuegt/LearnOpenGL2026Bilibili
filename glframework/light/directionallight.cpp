//
// Created by fengxuegt on 2026/3/16.
//

#include "directionallight.h"

DirectionalLight::DirectionalLight() {
}

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction) {
    mLightColor = color;
    mLightDirection = direction;
}

DirectionalLight::~DirectionalLight() {
}
