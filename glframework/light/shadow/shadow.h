//
// Created by fengxuegt on 2026/5/11.
//

#ifndef SHADOW_H
#define SHADOW_H
#include <camera.h>

#include "glframework/framebuffer.h"


class Shadow {
public:
    Shadow();
    ~Shadow();
    virtual void sentRenderTargetSize(int width, int height) = 0;
public:
    Camera *mCamera{nullptr};
    FrameBuffer *mRenderTarget{nullptr};
    float mBias{0.0003f};
    float mPcfRadius{0.0f};
    float mDiskTightness{1.0f};


};



#endif //SHADOW_H
