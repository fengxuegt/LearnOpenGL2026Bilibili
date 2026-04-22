//
// Created by fengxuegt on 2026/4/22.
//

#ifndef GAMECAMERACONTROL_H
#define GAMECAMERACONTROL_H
#include <cameracontrol.h>


class GameCameraControl : public CameraControl {
public:
    GameCameraControl();
    ~GameCameraControl();
    void onCursor(double xpos, double ypos);
    void update();
    void setSpeed(float speed);

private:
    void pitch(float angle);
    void yaw(float angle);

private:
    float mPitch{0.0f};
    float mSpeed{0.1f};



};



#endif //GAMECAMERACONTROL_H
