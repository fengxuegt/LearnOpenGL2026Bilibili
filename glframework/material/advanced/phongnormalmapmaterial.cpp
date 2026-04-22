//
// Created by fengxuegt on 2026/4/8.
//

#include "phongnormalmapmaterial.h"

PhongNormalMapMaterial::PhongNormalMapMaterial() {
    mType = MaterialType::PhongNormalMapMaterial;
}

PhongNormalMapMaterial::~PhongNormalMapMaterial() {
    if (mDiffuse) {
        delete mDiffuse;
    }
    if (mNormalMap) {
        delete mNormalMap;
    }
}
