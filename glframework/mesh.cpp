//
// Created by fengxuegt on 2026/3/16.
//

#include "mesh.h"

Mesh::Mesh() {
}

Mesh::Mesh(Geometry *geometry, Material *material) {
    mGeometry = geometry;
    mMaterial = material;
}

Mesh::~Mesh() {
}
