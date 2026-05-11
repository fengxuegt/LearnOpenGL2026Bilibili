//
// Created by fengxuegt on 2026/5/11.
//

#ifndef DIRECTIONALLIGHTSHADOW_H
#define DIRECTIONALLIGHTSHADOW_H
#include "shadow.h"


class DirectionalLightShadow : public Shadow {
public:
    DirectionalLightShadow();
    ~DirectionalLightShadow();
    void sentRenderTargetSize(int width, int height) override;
    glm::mat4 getLightMatrix(glm::mat4 lightModelMatrix);
public:


};



#endif //DIRECTIONALLIGHTSHADOW_H
