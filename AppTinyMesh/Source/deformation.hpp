#ifndef __DEFORMATION__
#define __DEFORMATION__

#include "AppTinyMesh/Source/surface.hpp"
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


Mesh deformation_forme_libre(const Mesh& mesh, const int n) {
    std::vector<Vector> verticies = mesh.get_verticies();
    std::vector<Vector> res;
    const Vector originPoint(0);
    res.reserve(verticies.size());
    for(const Vector& v : verticies) {
        Vector acc(0, 0, 0);
        for (int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                for (int z = 0; z < n; z++) {
                    Vector pc = v + Vector(float(x)/(n - 1), float(y)/(n - 1), float(z)/(n - 1));
                    float u = (pc - originPoint) * Vector().X;
                    float v = (pc - originPoint) * Vector().Y;
                    float w = (pc - originPoint) * Vector().Z;
                    acc += bernstein(n, x, u) * bernstein(n, y, v) * bernstein(n, z, w) * pc;
                }
            }
        }
        res.push_back(acc);
    }
    return Mesh(verticies, mesh.get_normals(), mesh.VertexIndexes(), mesh.NormalIndexes());
}

#endif