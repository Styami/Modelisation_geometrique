#ifndef __BOITE__
#define __BOITE__

#include "node.hpp"

class Boite : public Node {
    public:
        Boite(Boite&& b);
        Boite(const Boite& b);
        Boite(const Vector& min, const Vector& max);
        double value(const Vector& p) const override;
        Node* clone() const override;

    private:
        Vector pmin, pmax;
};

#endif