#ifndef __SURFACE__
#define __SURFACE__

#include "mesh.h"
#include <array>
#include <cstddef>

//template<int W, int H>
class Surface {
    public:
    Surface(int h, int w, int numPCH, int numPCW);
    Mesh get_mesh() const ;

    protected:
    virtual Vector calcul_vertex(const float u, const float v) const = 0;
    virtual Vector calcul_normal(const float u, const float v) const = 0;
    std::array<Vector, 49> pointsControls;


    inline const Vector& pointC(const size_t x, const size_t y) const;


    size_t height, width, numberControlPointH, numberControlPointW;

};

const Vector& Surface::pointC(const size_t x, const size_t y) const {
    return pointsControls[y * numberControlPointW + x];
}

static std::array<std::array<int, 10>, 10> NewtonalBinome{{
                                                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                            {1, 1 ,0, 0, 0, 0, 0, 0, 0, 0},
                                                            {1, 2, 1, 0, 0, 0, 0, 0, 0, 0},
                                                            {1, 3, 3, 1, 0, 0, 0, 0, 0, 0},
                                                            {1, 4, 6, 4, 1, 0, 0, 0, 0, 0},
                                                            {1, 5, 10, 10, 5, 1, 0, 0, 0, 0},
                                                            {1, 6, 15, 20, 15, 6, 1, 0, 0, 0},
                                                            {1, 7, 21, 35, 35, 21, 7, 1, 0, 0},
                                                            {1, 8, 28, 56, 70, 56, 28, 8, 1, 0},
                                                            {1, 9, 36, 84, 126, 126, 84, 36, 9, 1}
}};

inline float bernstein(int m, int i, float u)  {
    return NewtonalBinome[m-1][i] * std::pow(u, i) * std::pow(1 - u, (m -1) - i);
};





#endif