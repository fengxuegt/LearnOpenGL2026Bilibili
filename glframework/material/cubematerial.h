//
// Created by fengxuegt on 2026/3/26.
//

#ifndef CUBEMATERIAL_H
#define CUBEMATERIAL_H
#include <texture.h>

#include "material.h"


class CubeMaterial : public Material {
public:
    CubeMaterial();
    ~CubeMaterial();

public:
    Texture *mDiffuse;
};



#endif //CUBEMATERIAL_H
