#ifndef __TORE__
#define __TORE__

#include "node.hpp"

class Tore : public Node {
    public:
        Tore(Tore&& t);
        Tore(const Tore& t);
        Tore(const Vector& c, const Vector& n, const double r, const double R);
        double value(const Vector& p) const override;
        Node* clone() const override;

    private:
        Vector center, normal;
        //sr : small rayon
        //br : big rayon
        double sr, br;
};

#endif