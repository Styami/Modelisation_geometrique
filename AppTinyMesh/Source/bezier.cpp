#include "bezier.hpp"
#include "mathematics.h"
#include <cmath>
#include <cstddef>

Bezier::Bezier(int h, int w, int numPCH, int numPCW) : 
    Surface(std::max(h, 2), std::max(w, 2), std::min(numPCH, 10), std::min(numPCH, 10))
{}


Vector Bezier::calcul_normal(const float u, const float v) const {
    Vector normalU = Vector(0);
    Vector normalV = Vector(0);

    for(size_t i = 0; i < numberControlPointW - 1; i++) {
        for(size_t j = 0; j < numberControlPointH; j++) {
            const Vector& otherPoint = pointC(i+1, j);
            const Vector& currentPoint = pointC(i, j);
            normalU += numberControlPointW * (otherPoint - currentPoint)
                                * bernstein(numberControlPointW - 1, i, u)
                                * bernstein(numberControlPointH, j, v);
        }
    }
    for(size_t i = 0; i < numberControlPointW; i++) {
        for(size_t j = 0; j < numberControlPointH - 1; j++) {
            const Vector& otherPoint = pointC(i, j+1);
            const Vector& currentPoint = pointC(i, j);
            normalV += numberControlPointH * (otherPoint - currentPoint)
                                * bernstein(numberControlPointW, i, u)
                                * bernstein(numberControlPointH - 1, j, v);
        }
    }

    return normalU / normalV;
}

Vector Bezier::calcul_vertex(const float u, const float v) const {
    Vector res = Vector(0);

    for (size_t i = 0; i < numberControlPointW; i++) {
        for(size_t j = 0; j < numberControlPointH; j++) {
            res += bernstein(numberControlPointW, i, u)
                * bernstein(numberControlPointH, j, v)
                * pointC(i, j);
        }
    }

    return res;
}
