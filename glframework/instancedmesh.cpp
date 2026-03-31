//
// Created by fengxuegt on 2026/3/30.
//

#include "instancedmesh.h"

InstancedMesh::InstancedMesh() {
}

InstancedMesh::InstancedMesh(Geometry *geometry, Material *material, unsigned int instanceCount) : Mesh(geometry, material) {
    mType = ObjectType::InstanceMesh;
    mInstanceCount = instanceCount;
    mModelMatrices = new glm::mat4[instanceCount];
}

InstancedMesh::~InstancedMesh() {
    if (mModelMatrices) {
        delete[] mModelMatrices;
    }
}
