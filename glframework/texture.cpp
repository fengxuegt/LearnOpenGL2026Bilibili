//
// Created by fengxuegt on 2026/3/6.
//

#include "texture.h"
#include "stb_image.h"


Texture::Texture(const std::string &path, int unitID) {
    mUnitID = unitID;
    int width, height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    auto image_data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha); // unsigned char * data

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
    if (mTextureID != 0) {
        glDeleteTextures(1, &mTextureID);
    }
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}