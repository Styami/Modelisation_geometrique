#ifndef __Capsule__
#define __Capsule__

#include "node.hpp"

class Capsule : public Node {
    public:
        Capsule(Capsule&& c);
        Capsule(const Capsule& c);
        Capsule(const Vector& a, const Vector& b, const double r);
        double value(const Vector& p) const override;
        Node* clone() const override;

    private:
        // lp : lower point
        // up : upper point
        Vector lp, up;
        double rayon;
};

#endif