#include "sphere.hpp"
#include "mathematics.h"

Sphere::Sphere(const Vector& _c, const double _r) :
    center(_c),
    rayon(_r)
{}

Sphere::Sphere(const Sphere& s) :
    center(s.center),
    rayon(s.rayon)
{}

double Sphere::value(const Vector& p) const {
    return Norm(p - center) - rayon;
}

Node * Sphere::clone() const {
    return new Sphere(center, rayon);
}