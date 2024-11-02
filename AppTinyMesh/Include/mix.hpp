#ifndef __MIX__
#define __MIX__

#include "binaryExpr.hpp"

class Mix: public BinaryExpr {
    public:
        Mix(const Node& _n1, const Node& _n2, const double r);
        Mix(const Node* _n1, const Node* _n2, const double r);
        double value(const Vector& p) const override;
        Node* clone() const override;
    private:
        double offset(const double a, const double b) const;
        double mixRadius;
};

#endif