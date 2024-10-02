#include "surface.hpp"
#include "mathematics.h"
#include "mesh.h"
#include <cstddef>
#include <unistd.h>
#include <vector>

Surface::Surface(int h, int w, int numPCH, int numPCW) :
    height(h),
    width(w),
    numberControlPointH(numPCH),
    numberControlPointW(numPCW)
{
    pointsControls = {Vector{0, 10, 0}, Vector{10, -10, 0}, Vector{20, 20, 0}, Vector{30, -30, 0}, Vector{40, 40, 0}, Vector{50, 0, 0}, Vector{50, 0, 0},
                      Vector{0, -20, 10}, Vector{10, 10, 10}, Vector{20, -20, 10}, Vector{30, 30, 10}, Vector{40, -40, 10}, Vector{60, 40, 20}, Vector{40, 40, 30},
                      Vector{0, 30, 20}, Vector{10, -10, 20}, Vector{20, 20, 20}, Vector{30, -30, 20}, Vector{40, -40, 20}, Vector{50, 20, 20}, Vector{40, 0, 20},
                      Vector{0, -40, 30}, Vector{10, 10, 30}, Vector{20, -20, 30}, Vector{30, 30, 30}, Vector{40, 40, 30}, Vector{0, 0, 0}, Vector{-10, 0, 0},
                      Vector{0, 50, 40}, Vector{10, -10, 40}, Vector{20, 20, 40}, Vector{30, -30, 40}, Vector{40, -40, 40}, Vector{10, 0, 20}, Vector{0, 0, 10}, 
                      Vector{50, 50, 0}, Vector{40, 50, 40}, Vector{30, 50, 40}, Vector{20, 50, 40}, Vector{10, 50, 40}, Vector{0, 50, 40}, Vector{0, 50, 40}, 
                      Vector{60, 50, 0}, Vector{10, -10, 40}, Vector{20, 20, 40}, Vector{30, -30, 40}, Vector{40, -40, 40},  Vector{60, 0, 0}, Vector{100, 0, 0}
    };

}

Mesh Surface::get_mesh() const {
    std::vector<Vector> normals;
    std::vector<Vector> vertices;
    normals.reserve(width * height);
    vertices.reserve(width * height);

    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {      
            float u = float(x)/(width - 1);
            float v = float(y)/(height - 1);  
            vertices.push_back(calcul_vertex(u, v));
            normals.push_back(calcul_normal(u, v));
        }
    }

    std::vector<int> indiceN;
    indiceN.reserve((6 * width * height));
    for(size_t x = 0; x < width - 1; x++) {
        for (size_t y = 0; y < height - 1; y++) {
            indiceN.push_back(y * width + x);
            indiceN.push_back((y+1) * width + x);
            indiceN.push_back((y+1) * width + x+1);

            indiceN.push_back(y * width + x);
            indiceN.push_back((y+1) * width + (x+1));
            indiceN.push_back(y * width + (x + 1));
        }
    }

    return Mesh(vertices, normals, indiceN, indiceN);
}


