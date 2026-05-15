//
// Created by fengxuegt on 2026/3/26.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <texture.h>


class FrameBuffer {
public:
    static FrameBuffer* createShadowFbo(int width, int height);
    static FrameBuffer* createMultiSampleFbo(unsigned int width, unsigned int height, unsigned int samples);

    FrameBuffer(int width, int height);
    FrameBuffer();
    ~FrameBuffer();


public:
    int mWidth{2560};
    int mHeight{1440};
    GLuint mFbo{0};
    Texture *mColorAttachment{nullptr};
    Texture *mDepthStencilAttachment{nullptr};
    Texture *mDepthAttachment{nullptr};
};



#endif //FRAMEBUFFER_H
