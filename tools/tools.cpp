//
// Created by fengxuegt on 2026/3/18.
//

#include "tools.h"

void Tools::decompose(glm::mat4 matrix, glm::vec3 &position, glm::vec3 &eulerAngle, glm::vec3 &scale) {
    glm::quat quat;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(matrix, scale, quat, position, skew, perspective);
    glm::mat4 rotation = glm::toMat4(quat);
    glm::extractEulerAngleXYZ(rotation, eulerAngle.x, eulerAngle.y, eulerAngle.z);

    eulerAngle.x = glm::degrees(eulerAngle.x);
    eulerAngle.y = glm::degrees(eulerAngle.y);
    eulerAngle.z = glm::degrees(eulerAngle.z);
}
