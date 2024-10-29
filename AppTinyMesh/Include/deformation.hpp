#ifndef __DEFORMATION__
#define __DEFORMATION__

#include "surface.hpp"
#include "box.h"
#include "mathematics.h"
#include "mesh.h"
#include <algorithm>
#include <vector>

Mesh deformation_local(const Mesh& mesh, const Vector& center_def, const float rayon) {
    std::vector<Vector> new_pos;
    new_pos.reserve(mesh.get_verticies().size());
    for (const Vector& v : mesh.get_verticies()) {
        float distance = Norm(v - center_def) / rayon;
        distance = std::clamp(distance, float(0), float(1));
        Vector t = Normalized(v - center_def);
        Vector new_point = v + (1- distance * distance)*(1- distance * distance) * t;
        new_pos.push_back(new_point);
    }
    return Mesh(new_pos, mesh.get_normals(), mesh.VertexIndexes(), mesh.NormalIndexes());
}

Box transform_box(const Box& box) {
    Box copyBox = box;
    copyBox.Scale(2.75);
    return copyBox;
}

Vector trilinear_interpolation(const Box& box, const Vector& v) {

}


Mesh deformation_forme_libre(const Mesh& mesh, const int n) {
    Box boite = Box(2.0);
    Box transBox = transform_box(boite);
    //boite.Translate(Vector(1));
    transBox.Translate(Vector(1, 0, 0));
    std::vector<Vector> verticies = mesh.get_verticies();
    std::vector<Vector> res;
    const Vector lowerPointTrans(Mesh(transBox).get_verticies()[0]);
        const Vector lowerPoint(Mesh(boite).get_verticies()[0]);
    const Vector upperPointTrans(Mesh(transBox).get_verticies()[7]);
        const Vector upperPoint(Mesh(boite).get_verticies()[7]);
    res.reserve(verticies.size());
    for(const Vector& vertex : verticies) {
        if(!boite.Inside(vertex)){
            res.push_back(vertex);
            continue;
        }
        Vector acc(0, 0, 0);
        for (int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                for (int z = 0; z < n; z++) {
                    Vector pc = lowerPointTrans + Vector(float(x)/(n - 1), float(y)/(n - 1), float(z)/(n - 1));
                    Vector vecFromOrCube = vertex - lowerPoint;
                    float u = std::clamp((vecFromOrCube * Vector::X) / upperPoint[0], double(0), double(1));//std::clamp((pc - lowerPoint) * Vector::X, double(0), double(1)); // upperPoint[0]; //std::clamp((pc - lowerPoint)[0], double(0), double(1));
                    float v = std::clamp((vecFromOrCube * Vector::Y) / upperPoint[1], double(0), double(1));//std::clamp((pc - lowerPoint) * Vector::Y, double(0), double(1)); // upperPoint[1]; //std::clamp((pc - lowerPoint)[1], double(0), double(1));
                    float w = std::clamp((vecFromOrCube * Vector::Z) / upperPoint[2], double(0), double(1));//std::clamp((pc - lowerPoint) * Vector::Z, double(0), double(1)); // upperPoint[2]; //std::clamp((pc - lowerPoint)[2], double(0), double(1));
                    //std::cout << w << std::endl;
                    acc += bernstein(n, x, u) * bernstein(n, y, v) * bernstein(n, z, w) * pc;
                }
            }
        }
        res.push_back(acc);
    }
    return Mesh(res, mesh.get_normals(), mesh.VertexIndexes(), mesh.NormalIndexes());
}

#endif