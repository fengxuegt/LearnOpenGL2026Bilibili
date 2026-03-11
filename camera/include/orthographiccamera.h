//
// Created by fengxuegt on 2026/3/11.
//

#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H
#include <camera.h>


class OrthographicCamera : public Camera{
public:
    OrthographicCamera();
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
    ~OrthographicCamera();

    glm::mat4 getProjectionMatrix() override;

public:
    float mLeft{0.0f};
    float mRight{0.0f};
    float mBottom{0.0f};
    float mTop{0.0f};
    float mNear{0.0f};
    float mFar{0.0f};

};



#endif //ORTHOGRAPHICCAMERA_H
