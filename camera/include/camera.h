//
// Created by fengxuegt on 2026/3/11.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "core.h"


class Camera {

public:
    Camera();
    ~Camera();

    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();

public:
    glm::vec3 mPosition{0.0f, 0.0f, 1.0f}; // 摄像机的位置
    glm::vec3 mUp{0.0f, 1.0f, 0.0f}; // 穹顶向量
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};

};


#endif //CAMERA_H
