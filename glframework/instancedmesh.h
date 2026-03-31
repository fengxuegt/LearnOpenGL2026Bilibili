//
// Created by fengxuegt on 2026/3/30.
//

#ifndef INSTANCEDMESH_H
#define INSTANCEDMESH_H
#include <mesh.h>


class InstancedMesh : public Mesh{
public:
    void updateModelMatrices();

public:
    InstancedMesh();
    InstancedMesh(Geometry* geometry, Material* material, unsigned int instanceCount);
    ~InstancedMesh();

public:
    glm::mat4 *mModelMatrices{nullptr};
    unsigned int mInstanceCount{0};
    GLuint mModelMatrixVBO{0};
};



#endif //INSTANCEDMESH_H
