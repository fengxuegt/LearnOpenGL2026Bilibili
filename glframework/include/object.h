//
// Created by fengxuegt on 2026/3/16.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "core.h"

enum class ObjectType {
    Mesh,
    Object,
    Scene,
    InstanceMesh
};

class Object {
public:
    Object();
    virtual ~Object();

    void setPositon(glm::vec3 position);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void setAngleX(float angle);
    void setAngleY(float angle);
    void setAngleZ(float angle);

    void setScale(glm::vec3 scale);

    glm::mat4 getModelMatrix();
    glm::mat4 getModelMatrixAPI();

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();

    Object* getParent();
    void addChild(Object* child);
    std::vector<Object*> getChildren();

    ObjectType getType();

protected:
    glm::vec3 mPosition;  // 物体所处的位置
    float mAngleX{0.0f}; // 物体绕X轴旋转的角度    上下点头
    float mAngleY{0.0f}; // 物体绕Y轴旋转的角度    左右摇头
    float mAngleZ{0.0f}; // 物体绕Z轴旋转的角度    翻转自己

    glm::vec3 mScale{1.0f, 1.0f, 1.0f};

    // parent and child
    std::vector<Object*> mChildren{};
    Object *mParent{nullptr};
    ObjectType mType{ObjectType::Mesh};



};

inline std::vector<Object *> Object::getChildren() {
    return mChildren;
}

inline ObjectType Object::getType() {
    return mType;
}


#endif //OBJECT_H
