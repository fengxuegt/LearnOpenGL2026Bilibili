//
// Created by fengxuegt on 2026/3/16.
//

#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include <texture.h>
#include "material.h"


class PhongMaterial : public Material{
public:
    PhongMaterial();
    ~PhongMaterial();
public:
    Texture *mDiffuse{nullptr};
    float mShininess {1.0f};


};



#endif //PHONGMATERIAL_H
