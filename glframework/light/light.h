//
// Created by fengxuegt on 2026/3/16.
//

#ifndef LIGHT_H
#define LIGHT_H

#include <object.h>

#include "core.h"
#include "shadow/shadow.h"

class Light : public Object{
public:
    Light();
    Light(glm::vec3 color);
    ~Light();

public:
    glm::vec3 mLightColor{1.0f};
    float mLightIntensity{1.0f};

    Shadow *mShadow{nullptr};
};



#endif //LIGHT_H
