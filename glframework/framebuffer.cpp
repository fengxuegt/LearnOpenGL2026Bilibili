//
// Created by fengxuegt on 2026/3/26.
//

#include "framebuffer.h"

FrameBuffer * FrameBuffer::createShadowFbo(int width, int height) {
    FrameBuffer * fbo = new FrameBuffer();
    fbo->mWidth = width;
    fbo->mHeight = height;
    glGenFramebuffers(1, &fbo->mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->mFbo);
    fbo->mDepthAttachment = Texture::createDepthAttachment(width, height, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, fbo->mDepthAttachment->getTextureID(), 0);
    glDrawBuffer(GL_NONE);  // 显示告诉OpenGL，我们当前的fbo没有颜色输出
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return fbo;

}

FrameBuffer * FrameBuffer::createMultiSampleFbo(unsigned int width, unsigned int height, unsigned int samples) {
    FrameBuffer * fb = new FrameBuffer();
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    auto colorAttachment = Texture::createMultisampleTexture(width, height, samples, GL_RGBA, 0);
    auto dsAttachment = Texture::createMultisampleTexture(width, height, samples, GL_DEPTH24_STENCIL8, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorAttachment->getTextureID(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, dsAttachment->getTextureID(), 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    fb->mFbo = fbo;
    fb->mDepthStencilAttachment = dsAttachment;
    fb->mColorAttachment = colorAttachment;
    fb->mWidth = width;
    fb->mHeight = height;
    return fb;
}

FrameBuffer::FrameBuffer(int width, int height) {
    mWidth = width;
    mHeight = height;
    glGenFramebuffers(1, &mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    mColorAttachment = Texture::createColorAttachment(mWidth, mHeight, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, mColorAttachment->getTextureID(), 0);

    mDepthStencilAttachment = Texture::createDepthStencilAttachment(mWidth, mHeight, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D, mDepthStencilAttachment->getTextureID(), 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER::FRAMEBUFFER" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::FrameBuffer() {
}

FrameBuffer::~FrameBuffer() {
    if (mFbo != 0) {
        glDeleteFramebuffers(1, &mFbo);
    }
    if (mColorAttachment != nullptr) {
        delete mColorAttachment;
    }
    if (mDepthStencilAttachment != nullptr) {
        delete mDepthStencilAttachment;
    }
}
