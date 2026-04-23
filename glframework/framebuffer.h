//
// Created by fengxuegt on 2026/3/26.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <texture.h>


class FrameBuffer {
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();


public:
    int mWidth{2560};
    int mHeight{1440};
    GLuint mFbo{0};
    Texture *mColorAttachment{nullptr};
    Texture *mDepthStencilAttachment{nullptr};

};



#endif //FRAMEBUFFER_H
