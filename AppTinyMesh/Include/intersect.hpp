#ifndef __INTERSECT__
#define __INTERSECT__

#include "binaryExpr.hpp"

class Intersect: public BinaryExpr {
    public:
        Intersect(const Node& _n1, const Node& _n2);
        Intersect(const Node* _n1, const Node* _n2);
        double value(const Vector& p) const override;
        Node* clone() const override;
};

#endif