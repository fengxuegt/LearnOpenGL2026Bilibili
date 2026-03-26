//
// Created by fengxuegt on 2026/3/26.
//

#include "framebuffer.h"

FrameBuffer::FrameBuffer(int width, int height) {
    glGenFramebuffers(1, &mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    mColorAttachment = Texture::createColorAttachment(mWidth, mHeight, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, mColorAttachment->getTextureID(), 0);

    mDepthStencilAttachment = Texture::createDepthAttachment(mWidth, mHeight, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D, mDepthStencilAttachment->getTextureID(), 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER::FRAMEBUFFER" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
