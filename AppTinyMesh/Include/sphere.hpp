#ifndef __SPHERE__
#define __SPHERE__

#include "node.hpp"
class Sphere : public Node {
    public:
        Sphere(const Sphere& s);
        Sphere(Sphere&& s);
        Sphere(const Vector& _c, const double _r);
        double value(const Vector& p) const override;
        Node* clone() const override;

    private:
        Vector center;
        double rayon;
};

#endif