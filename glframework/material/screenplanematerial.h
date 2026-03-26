//
// Created by fengxuegt on 2026/3/26.
//

#ifndef SCREENPLANEMATERIAL_H
#define SCREENPLANEMATERIAL_H
#include <texture.h>

#include "material.h"


class ScreenPlaneMaterial : public Material {
public:
    ScreenPlaneMaterial();
    ~ScreenPlaneMaterial();

public:
    Texture *mDiffuse{nullptr};
    float mShininess{1.0f};

};



#endif //SCREENPLANEMATERIAL_H
