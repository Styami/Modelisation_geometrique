#include "intersect.hpp"
#include "binaryExpr.hpp"

Intersect::Intersect(const Node& _n1, const Node& _n2) :
    BinaryExpr(_n1, _n2)
{}

Intersect::Intersect(const Node* _n1, const Node* _n2) :
    BinaryExpr(_n1, _n2)
{}

double Intersect::value(const Vector& p) const {
    return std::max(n1->value(p), -n2->value(p));
}

Node* Intersect::clone() const {
    return new Intersect(*n1->clone(), *n2->clone());
}