//
// Created by fengxuegt on 2026/3/16.
//

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "light.h"


class DirectionalLight : public Light{
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 color, glm::vec3 direction);
    ~DirectionalLight();


public:
    glm::vec3 mLightDirection{-1.0f};
};



#endif //DIRECTIONALLIGHT_H
