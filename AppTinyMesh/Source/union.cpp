#include "union.hpp"
#include "binaryExpr.hpp"


Union::Union(const Node& _n1, const Node& _n2) :
    BinaryExpr(_n1.clone(), _n2.clone())
{}

Union::Union(const Node* _n1, const Node* _n2) :
    BinaryExpr(_n1, _n2)
{}

double Union::value(const Vector& p) const {
    return std::min(n1->value(p), n2->value(p));
}

Node* Union::clone() const {
    return new Union(*n1->clone(), *n2->clone());
}