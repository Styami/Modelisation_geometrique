#include "capsule.hpp"
#include "mathematics.h"
#include <cmath>

Capsule::Capsule(const Vector& a, const Vector& b, const double r) :
    lp(a),
    up(b),
    rayon(r)
{}

double Capsule::value(const Vector& p) const {
    const Vector normal = Normalized(up - lp);
    const Vector lpToP = p - lp;
    double height = normal * lpToP;
    if(height <= 0)
        return Norm(lpToP) - rayon;
    else if (height >= Norm(up - lp))
        return Norm(p - up) - rayon;

    return std::sqrt(Norm(lpToP) * Norm(lpToP) - height * height) - rayon; 
}


Node* Capsule::clone() const {
    return new Capsule(lp, up, rayon);
}