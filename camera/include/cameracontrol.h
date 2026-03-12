//
// Created by fengxuegt on 2026/3/11.
//

#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H
#include <camera.h>
#include <map>


class CameraControl {

public:
    virtual void onMouse(int button, int action, double xpos, double ypos);
    virtual void onCursor(float xpos, float ypos);
    virtual void onKey(int key, int action, int mods);
    virtual void onScroll(double yoffset);
    virtual void update();

    void setCamera(Camera *camera) {
        mCamera = camera;
    }
    void setSensitivity(float sensitivity) {
        mSensitivity = sensitivity;
    }

public:
    CameraControl();
    ~CameraControl();

public:
    // 鼠标按键的状态
    bool mLeftMouseButtonDown = false;
    bool mRightMouseButtonDown = false;
    bool mMiddleMouseButtonDown = false;

    // 鼠标位置
    float mCurrentX = 0.0f;
    float mCurrentY = 0.0f;

    // 键盘状态存储
    std::map<int, bool> mKeyMap;

    // 敏感度
    float mSensitivity = 0.1f;

    Camera *mCamera{nullptr};


};



#endif //CAMERACONTROL_H
