//
// Created by fengxuegt on 2026/4/22.
//

#include "phongparallaxmapmaterial.h"

PhongParallaxMapMaterial::PhongParallaxMapMaterial() {
    mType = MaterialType::PhongParallaxMapMaterial;
}

PhongParallaxMapMaterial::~PhongParallaxMapMaterial() {
    if (mDiffuse) {
        delete mDiffuse;
    }
    if (mNormalMap) {
        delete mNormalMap;
    }
    if (mParallaxMap) {
        delete mParallaxMap;
    }
}
