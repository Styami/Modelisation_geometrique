#ifndef __SURFACE__
#define __SURFACE__


#include "mathematics.h"
#include "mesh.h"
#include <array>
#include <cstddef>
#include <vector>

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


    int height, width, numberControlPointH, numberControlPointW;

};

const Vector& Surface::pointC(const size_t x, const size_t y) const {
    return pointsControls[y * numberControlPointW + x];
}



#endif