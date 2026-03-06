//
// Created by fengxuegt on 2026/3/6.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "core.h"

class Texture {

public:
    Texture(const std::string &path, int unitID);
    ~Texture();

public:
    void Bind();

private:
    GLuint mTextureID;
    GLuint mUnitID;

};




#endif //TEXTURE_H
