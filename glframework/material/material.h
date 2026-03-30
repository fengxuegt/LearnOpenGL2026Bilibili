//
// Created by fengxuegt on 2026/3/16.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include <glad/glad.h>


enum class MaterialType {
    PhongMaterial,
    WhiteMaterial,
    ScreenPlaneMaterial,
    CubeMaterial
};
class Material {
public:
    Material();
    Material(MaterialType type);
    MaterialType getType();
    ~Material();

public:
    MaterialType mType;

    // depth test
    bool mDepthTest{true};
    GLenum mDepthFun{GL_LEQUAL};
    bool mDepthWrite{true};

};



#endif //MATERIAL_H
