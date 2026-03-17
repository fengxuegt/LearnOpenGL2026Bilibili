//
// Created by fengxuegt on 2026/3/16.
//

#include "object.h"

Object::Object() {
    mType = ObjectType::Object;
}

Object::~Object() {
}

void Object::setPositon(glm::vec3 position) {
    mPosition = position;
}

void Object::rotateX(float angle) {
    mAngleX += angle;
}

void Object::rotateY(float angle) {
    mAngleY += angle;
}

void Object::rotateZ(float angle) {
    mAngleZ += angle;
}

void Object::setScale(glm::vec3 scale) {
    mScale = scale;
}

glm::mat4 Object::getModelMatrix() {
    glm::mat4 parentlMatrix = glm::mat4(1.0f);
    if (mParent) {
        parentlMatrix = mParent->getModelMatrix();
    }

    // unity 缩放  旋转  平移
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, mScale);

    // unity的旋转标准 Pitch  yaw  roll
    model = glm::rotate(model, glm::radians(mAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));

    model = parentlMatrix * glm::translate(glm::mat4(1.0f), mPosition) * model;
    return model;
}
glm::mat4 Object::getModelMatrixAPI()
{
    glm::mat4 model(1.0f);

    model = glm::translate(model, mPosition);

    model = glm::rotate(model, glm::radians(mAngleZ), glm::vec3(0,0,1));
    model = glm::rotate(model, glm::radians(mAngleY), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(mAngleX), glm::vec3(1,0,0));

    model = glm::scale(model, mScale);
    glm::mat4 parentlMatrix = glm::mat4(1.0f);
    if (mParent) {
        return parentlMatrix = mParent->getModelMatrix() * model;
    }

    return model;
}

void Object::setPosition(glm::vec3 position) {
    mPosition = position;
}

Object* Object::getParent() {
    return mParent;
}

void Object::addChild(Object *child) {
    auto it = std::find(mChildren.begin(), mChildren.end(), child);
    if (it != mChildren.end()) {
        std::cerr << "Already added." << std::endl;
    }
    mChildren.push_back(child);
    child->mParent = this;
}
