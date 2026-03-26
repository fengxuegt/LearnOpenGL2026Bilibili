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
    int mWidth{1600};
    int mHeight{1200};
    GLuint mFbo{0};
    Texture *mColorAttachment{nullptr};
    Texture *mDepthStencilAttachment{nullptr};

};



#endif //FRAMEBUFFER_H
