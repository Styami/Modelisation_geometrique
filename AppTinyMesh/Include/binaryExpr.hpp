#ifndef __BINARYEXPRE__
#define __BINARYEXPRE__

#include "node.hpp"

class BinaryExpr : public Node {
    public:
        virtual ~BinaryExpr() {
            delete n1;
            delete n2;
        }
    protected:
        BinaryExpr(const Node& _n1, const Node& _n2) :
            n1(_n1.clone()),
            n2(_n2.clone())
        {}
        BinaryExpr(const Node* _n1, const Node* _n2) :
            n1(_n1->clone()),
            n2(_n2->clone())
        {}
        Node* n1, * n2;
};

#endif