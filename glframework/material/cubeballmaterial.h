//
// Created by fengxuegt on 2026/3/31.
//

#ifndef CUBEBALLMATERIAL_H
#define CUBEBALLMATERIAL_H
#include <texture.h>

#include "material.h"


class CubeBallMaterial : public Material{
public:
    CubeBallMaterial();
    ~CubeBallMaterial();
public:
    Texture *mDiffuse{nullptr};

};



#endif //CUBEBALLMATERIAL_H
