//
// Created by fengxuegt on 2026/4/22.
//

#ifndef PHONGPARALLAXMAPMATERIAL_H
#define PHONGPARALLAXMAPMATERIAL_H
#include <texture.h>
#include <glframework/material/material.h>


class PhongParallaxMapMaterial : public Material {
public:
    PhongParallaxMapMaterial();
    ~PhongParallaxMapMaterial();

public:
    Texture *mDiffuse{nullptr};
    Texture *mNormalMap{nullptr};
    Texture *mParallaxMap{nullptr};
    float mShininess{64.0f};
    float mHeightScale{0.1f};
};



#endif //PHONGPARALLAXMAPMATERIAL_H
