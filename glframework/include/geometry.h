//
// Created by fengxuegt on 2026/3/12.
//

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "core.h"

class Geometry {
public:
    Geometry();
    ~Geometry();
public:
    GLuint getVao();
    GLuint getIndicesCount();

    static Geometry *createBox(float size);
    static Geometry *createSphere(float size);
    static Geometry *createPlane(float width, float height);


public:
    GLuint mVao = 0;
    GLuint mPosVbo = 0;
    GLuint mUvVbo = 0;
    GLuint mEbo = 0;
    GLuint mIndicesCount = 0;


};



#endif //GEOMETRY_H
