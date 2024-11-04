#include "boite.hpp"
#include <algorithm>

Boite::Boite(const Vector& a, const Vector& b) :
    pmin(a),
    pmax(b)
{}

double Boite::value(const Vector& p) const {
    Vector closestPoint(0, 0, 0);
    closestPoint[0] = std::max(std::min(pmax[0], p[0]), pmin[0]);
    closestPoint[1] = std::max(std::min(pmax[1], p[1]), pmin[1]);
    closestPoint[2] = std::max(std::min(pmax[2], p[2]), pmin[2]);
    return Norm(p - closestPoint);
}

Node* Boite::clone() const {
    return new Boite(pmin, pmax);
}