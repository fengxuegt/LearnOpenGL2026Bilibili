//
// Created by fengxuegt on 2026/3/16.
//

#ifndef MESH_H
#define MESH_H
#include "object.h"
#include "../material/material.h"
#include "geometry.h"


class Mesh : public Object{
public:
    Mesh();
    Mesh(Geometry* geometry, Material* material);
    ~Mesh();

public:
    Geometry* mGeometry{nullptr};
    Material* mMaterial{nullptr};
};



#endif //MESH_H
