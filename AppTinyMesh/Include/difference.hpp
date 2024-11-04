#ifndef __DIFFERENCE__
#define __DIFFERENCE__

#include "binaryExpr.hpp"

class Difference: public BinaryExpr {
    public:
        Difference(const Node& _n1, const Node& _n2);
        Difference(const Node* _n1, const Node* _n2);
        double value(const Vector& p) const override;
        Node* clone() const override;
};

#endif