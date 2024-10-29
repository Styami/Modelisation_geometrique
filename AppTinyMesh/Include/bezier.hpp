#ifndef __BEZIER__
#define __BEZIER__

#include "mathematics.h"
#include"surface.hpp"
#include <array>

class Bezier : public Surface {
    public :
        Bezier(int h, int w, int numPCH, int numPCW);
    private:
        Vector calcul_vertex(const float u, const float v) const override;
        Vector calcul_normal(const float x, const float y) const override;
};


#endif
