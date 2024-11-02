#include "mix.hpp"
#include "binaryExpr.hpp"
#include <algorithm>
#include <cstdlib>

Mix::Mix(const Node& _n1, const Node& _n2, const double r) :
    BinaryExpr(_n1.clone(), _n2.clone()),
    mixRadius(r)
{}

double Mix::offset(const double a, const double b) const {
    double h = std::max(mixRadius - std::abs(a - b), 0.0) / mixRadius;
    return mixRadius * h * h * h / 6;
}

double Mix::value(const Vector& p) const {
    const double a = n1->value(p);
    const double b = n2->value(p);
    return std::min(a, b) - offset(a, b);
}

Node* Mix::clone() const {
    return new Mix(*n1->clone(), *n2->clone(), mixRadius);
}