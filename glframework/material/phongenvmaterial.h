//
// Created by fengxuegt on 2026/3/30.
//

#ifndef PHONGENVMATERIAL_H
#define PHONGENVMATERIAL_H
#include <texture.h>

#include "material.h"


class PhongEnvMaterial : public Material {
public:
    PhongEnvMaterial();
    ~PhongEnvMaterial();
public:
    Texture *mDiffuse{nullptr};
    Texture *mCubeMap{nullptr};
    float mShininess {1.0f};
};



#endif //PHONGENVMATERIAL_H
