//
// Created by fengxuegt on 2026/3/12.
//

#include "geometry.h"

Geometry::Geometry() {
}

Geometry::~Geometry() {
    if (mVao) {
        glDeleteVertexArrays(1, &mVao);
    }
    if (mPosVbo) {
        glDeleteBuffers(1, &mPosVbo);
    }
    if (mUvVbo) {
        glDeleteBuffers(1, &mUvVbo);
    }
    if (mEbo) {
        glDeleteBuffers(1, &mEbo);
    }
}

GLuint Geometry::getVao() {
    return mVao;
}

GLuint Geometry::getIndicesCount() {
    return mIndicesCount;
}

Geometry * Geometry::createBox(float size) {
    Geometry *box = new Geometry();
    return box;
}
Geometry *Geometry::createPlane(float width, float height) {
    Geometry *geometry = new Geometry();
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    float data [] = {
        -hw,  hh, 0.0f,   1,0,0,  0,1,
         hw,  hh, 0.0f,   0,1,0,  1,1,
        -hw, -hh, 0.0f,   0,0,1,  0,0,
         hw, -hh, 0.0f,   0,0,1,  1,0
    };

    unsigned int ebos[] = {
        0, 1, 2,
        1, 3, 2,
    };
    geometry->mIndicesCount = 6;
    glGenVertexArrays(1, &geometry->mVao);
    glBindVertexArray(geometry->mVao);
    glGenBuffers(1, &geometry->mPosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);


    glGenBuffers(1, &geometry->mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebos), ebos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
    glBindVertexArray(0);
    return geometry;
}


Geometry * Geometry::createSphere(float size) {
    Geometry *geometry = new Geometry();
    return geometry;
}

