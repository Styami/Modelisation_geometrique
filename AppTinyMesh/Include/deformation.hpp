#ifndef __DEFORMATION__
#define __DEFORMATION__

#include "surface.hpp"
#include "box.h"
#include "mathematics.h"
#include "mesh.h"
#include <algorithm>
#include <cstddef>
#include <vector>

Mesh deformation_local(const Mesh& mesh, const Vector& center_def, const float rayon) {
    std::vector<Vector> new_pos;
    std::vector<Vector> new_norm;
    const std::vector<Vector>& normalsMesh = mesh.get_normals();
    const std::vector<Vector>& verticiesMesh = mesh.get_verticies();
    new_norm .reserve(mesh.get_normals().size());
    new_pos.reserve(mesh.get_verticies().size());
    for (size_t i = 0; i < verticiesMesh.size(); i++) {
        float distance = Norm(verticiesMesh[i] - center_def) / rayon;
        distance = std::clamp(distance, float(0), float(1));
        Vector t = Normalized(verticiesMesh[i] - center_def) * 6;
        Vector new_point = verticiesMesh[i] + (1- distance * distance)*(1- distance * distance) * t;
        new_pos.push_back(new_point);
        new_norm.push_back(Lerp(Normalized(new_point - center_def), normalsMesh[i], 0.5));

    }
    return Mesh(new_pos, new_norm, mesh.VertexIndexes(), mesh.NormalIndexes());
}

Box transform_box(const Box& box) {
    Box copyBox = box;
    copyBox.Scale(0.75);
    return copyBox;
}

Vector trilinear_interpolation(const Box& box, const Vector& v) {
    double xd = (v[0] - box[0][0]) / (box[1][0] - box[0][0]);
    double yd = (v[1] - box[0][1]) / (box[1][1] - box[0][1]);
    double zd = (v[2] - box[0][2]) / (box[1][2] - box[0][2]);    

    Vector c00 = box.Vertex(0) * (1 - xd) + box.Vertex(1) * xd;
    Vector c01 = box.Vertex(4) * (1 - xd) + box.Vertex(5) * xd;
    Vector c10 = box.Vertex(2) * (1 - xd) + box.Vertex(3) * xd;
    Vector c11 = box.Vertex(6) * (1 - xd) + box.Vertex(7) * xd;

    Vector c0 = c00 * (1 - yd) + c10 * yd;
    Vector c1 = c01 * (1 - yd) + c11 * yd;

    return c0 * (1 - zd) + c1 * zd;
}


Mesh deformation_forme_libre(const Mesh& mesh) {
    Box boite = Box(10.0);
    Box transBox = transform_box(boite);
    transBox.Translate(Vector(-5, 0, 0));
    std::vector<Vector> verticies = mesh.get_verticies();
    std::vector<Vector> res;
    res.reserve(verticies.size());
    for(const Vector& vertex : verticies) {
        if(!boite.Inside(vertex)){
            res.push_back(vertex);
            continue;
        }
        res.push_back(trilinear_interpolation(transBox, vertex));
    }
    return Mesh(res, mesh.get_normals(), mesh.VertexIndexes(), mesh.NormalIndexes());
}

#endif