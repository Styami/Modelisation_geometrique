#include "tore.hpp"
#include <cmath>

Tore::Tore(const Vector& c, const Vector& n, const double r, const double R) :
    center(c),
    normal(Normalized(n)),
    sr(r),
    br(R)
{}

double Tore::value(const Vector& p) const {
    Vector cp = p - center;
    double height = cp * normal;
    double base = cp * cp - height * height;
    base = std::sqrt(base) - br;
    double length = height * height + base * base;
    return length - sr;
}

Node* Tore::clone() const {
    return new Tore(center, normal, sr, br);
}