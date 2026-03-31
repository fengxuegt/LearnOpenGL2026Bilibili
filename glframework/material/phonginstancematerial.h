//
// Created by fengxuegt on 2026/3/31.
//

#ifndef PHONGINSTANCEMATERIAL_H
#define PHONGINSTANCEMATERIAL_H
#include <texture.h>

#include "material.h"


class PhongInstanceMaterial : public Material {
public:
    PhongInstanceMaterial();
    ~PhongInstanceMaterial();


public:
    Texture *mDiffuse{nullptr};
    float mShininess {1.0f};


};



#endif //PHONGINSTANCEMATERIAL_H
