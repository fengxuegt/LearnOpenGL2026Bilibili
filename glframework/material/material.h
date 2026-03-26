//
// Created by fengxuegt on 2026/3/16.
//

#ifndef MATERIAL_H
#define MATERIAL_H


enum class MaterialType {
    PhongMaterial,
    WhiteMaterial,
    ScreenPlaneMaterial
};
class Material {
public:
    Material();
    Material(MaterialType type);
    MaterialType getType();
    ~Material();

public:
    MaterialType mType;

};



#endif //MATERIAL_H
