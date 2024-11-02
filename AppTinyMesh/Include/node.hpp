#ifndef __NODE__
#define __NODE__

#include "mathematics.h"
class Node {
    public:
        virtual double value(const Vector& p) const = 0;
        virtual Node* clone() const = 0;
        virtual ~Node() {};
};


#endif