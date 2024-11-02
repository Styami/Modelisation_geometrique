#ifndef __UNON__
#define __UNON__

#include "binaryExpr.hpp"

class Union: public BinaryExpr {
    public:
        Union(const Node& _n1, const Node& _n2);
        Union(const Node* _n1, const Node* _n2);
        Node* clone() const override;
        double value(const Vector& p) const override;
};

#endif