//
// Created by fengxuegt on 2026/3/26.
//

#include "cubematerial.h"

CubeMaterial::CubeMaterial() {
    mType = MaterialType::CubeMaterial;
}

CubeMaterial::~CubeMaterial() {
    if (mDiffuse) {
        delete mDiffuse;
    }
}
