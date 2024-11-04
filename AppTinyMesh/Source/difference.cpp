#include "difference.hpp"

Difference::Difference(const Node& _n1, const Node& _n2) :
    BinaryExpr(_n1, _n2)
{}

Difference::Difference(const Node* _n1, const Node* _n2) :
    BinaryExpr(_n1, _n2)
{}

double Difference::value(const Vector& p) const {
    return std::max(n1->value(p), -n2->value(p));
}

Node* Difference::clone() const {
    return new Difference(*n1->clone(), *n2->clone());
}