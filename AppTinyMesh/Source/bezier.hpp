#ifndef __BEZIER__
#define __BEZIER__

#include "mathematics.h"
#include"surface.hpp"
#include <array>

class Bezier : public Surface {
    public :
        Bezier(int h, int w, int numPCH, int numPCW);
    private:
        inline float bernstein(int m, int i, float u) const;
        Vector calcul_vertex(const float u, const float v) const override;
        Vector calcul_normal(const float x, const float y) const override;
        std::array<std::array<int, 10>, 10> NewtonalBinome{{
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
};

float Bezier::bernstein(int m, int i, float u) const {
    int coefBin = NewtonalBinome[m-1][i];
    float upow = std::pow(u, i);
    float invUPow = std::pow(1 - u, (m -1) - i);
    float res = coefBin * upow * invUPow; 
    return res;
}


#endif
