//
// Created by fengxuegt on 2026/3/12.
//

#ifndef TRACKBALLCAMERACONTROL_H
#define TRACKBALLCAMERACONTROL_H
#include <cameracontrol.h>


class TrackBallCameraControl :public CameraControl{
public:

    TrackBallCameraControl();
    ~TrackBallCameraControl();

    void onCursor(float xpos, float ypos) override;
    void onScroll(double yoffset) override;


private:
    void pitch(float angle);
    void yaw(float angle);

    float moveSpeed = 0.01f; // 中键移动速度
    float mScaleSpeed = 0.01f; // 滚轮缩放速度
};




#endif //TRACKBALLCAMERACONTROL_H
