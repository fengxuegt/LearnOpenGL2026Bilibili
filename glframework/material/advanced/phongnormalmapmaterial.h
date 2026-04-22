//
// Created by fengxuegt on 2026/4/8.
//

#ifndef PHONGNORMALMAPMATERIAL_H
#define PHONGNORMALMAPMATERIAL_H
#include <texture.h>
#include <glframework/material/material.h>


class PhongNormalMapMaterial : public Material{
public:
    PhongNormalMapMaterial();
    virtual ~PhongNormalMapMaterial();

public:
    Texture *mDiffuse{nullptr};
    Texture *mNormalMap{nullptr};
    float mShininess{64.0f};


};



#endif //PHONGNORMALMAPMATERIAL_H
