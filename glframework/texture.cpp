//
// Created by fengxuegt on 2026/3/6.
//

#include "texture.h"
#include "stb_image.h"

std::map<std::string, Texture*> Texture::mTextureCache{};

Texture::Texture() {
}

Texture * Texture::createTexture(const std::string &path, unsigned int unit) {
    auto it = mTextureCache.find(path);
    if (it != mTextureCache.end()) {
        return it->second;
    }
    auto texture = new Texture(path, unit);
    mTextureCache[path] = texture;
    return texture;
}

Texture * Texture::createTextureFromMemory(const std::string &path, unsigned int unit, unsigned char *dataIn,
    uint32_t widthIn, uint32_t heightIn) {
    auto it = mTextureCache.find(path);
    if (it != mTextureCache.end()) {
        return it->second;
    }
    auto texture = new Texture(unit, dataIn, widthIn, heightIn);
    mTextureCache[path] = texture;
    return texture;
}

Texture * Texture::createColorAttachment(int width, int height, int unitID) {
    Texture *colorAttachment = new Texture();
    colorAttachment->mWidth = width;
    colorAttachment->mHeight = height;
    colorAttachment->mTextureID = unitID;
    glGenTextures(1, &colorAttachment->mTextureID);
    glActiveTexture(GL_TEXTURE0 + unitID);
    glBindTexture(GL_TEXTURE_2D, colorAttachment->mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return colorAttachment;


}

Texture * Texture::createDepthAttachment(int width, int height, int unitID) {
    Texture *depthAttachment = new Texture();
    depthAttachment->mWidth = width;
    depthAttachment->mHeight = height;
    depthAttachment->mUnitID = unitID;
    glGenTextures(1, &depthAttachment->mTextureID);
    glActiveTexture(GL_TEXTURE0 + unitID);
    glBindTexture(GL_TEXTURE_2D, depthAttachment->mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return depthAttachment;
}

Texture::Texture(const std::string &path, int unitID) {
    mUnitID = unitID;
    int width, height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    auto image_data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha); // unsigned char * data

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(unsigned int unit, unsigned char *dataIn, uint32_t widthIn, uint32_t heightIn) {
    mUnitID = unit;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    uint32_t dataInSize = 0;
    if (!heightIn) {
        dataInSize = widthIn;
    } else {
        dataInSize = widthIn * heightIn * 4;
    }
    unsigned char *data = stbi_load_from_memory(dataIn, dataInSize, &mWidth, &mHeight, &channels, STBI_rgb_alpha);
    glGenTextures(1, &mTextureID);
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

// right left up down back front   + x   - x    +y    -y    +z   -z
Texture::Texture(std::vector<std::string> &paths, int unit) {
    mTextureTarget = GL_TEXTURE_CUBE_MAP;
    mUnitID = unit;
    glGenTextures(1, &mTextureID);
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);
    stbi_set_flip_vertically_on_load(false);
    int channels;
    int width, height;
    unsigned char* data = nullptr;
    for (int i = 0; i < paths.size(); i++) {
        data = stbi_load(paths[i].c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Texture failed to load at path: " << paths[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(mTextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(mTextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture() {
    if (mTextureID != 0) {
        glDeleteTextures(1, &mTextureID);
    }
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glBindTexture(mTextureTarget, mTextureID);
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}
