//
// Created by fengxuegt on 2026/3/30.
//

#include "instancedmesh.h"

void InstancedMesh::updateModelMatrices() {
    glBindBuffer(GL_ARRAY_BUFFER, mModelMatrixVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4) * mInstanceCount, mModelMatrices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

InstancedMesh::InstancedMesh() {
}

InstancedMesh::InstancedMesh(Geometry *geometry, Material *material, unsigned int instanceCount) : Mesh(geometry, material) {
    mType = ObjectType::InstanceMesh;
    mInstanceCount = instanceCount;
    mModelMatrices = new glm::mat4[instanceCount];
    glGenBuffers(1, &mModelMatrixVBO);
    glBindVertexArray(geometry->getVao());
    glBindBuffer(GL_ARRAY_BUFFER, mModelMatrixVBO);
    glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(glm::mat4), mModelMatrices, GL_DYNAMIC_DRAW);
    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (sizeof(float) * i * 4));
        glVertexAttribDivisor(3 + i, 1);
    }
    glBindVertexArray(0);

}

InstancedMesh::~InstancedMesh() {
    if (mModelMatrices) {
        delete[] mModelMatrices;
    }
}
