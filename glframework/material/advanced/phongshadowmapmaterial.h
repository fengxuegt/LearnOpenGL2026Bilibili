//
// Created by fengxuegt on 2026/5/7.
//

#ifndef PHONGSHADOWMAPMATERIAL_H
#define PHONGSHADOWMAPMATERIAL_H
#include <texture.h>
#include <glframework/material/material.h>


class PhongShadowMapMaterial : public Material{
public:
    PhongShadowMapMaterial();
    virtual ~PhongShadowMapMaterial();


public:
    Texture *mDiffuse{nullptr};
    Texture * mSpecularMask{nullptr};
    float mShininess {1.0f};
};



#endif //PHONGSHADOWMAPMATERIAL_H
