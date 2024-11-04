#ifndef __BINARYEXPRE__
#define __BINARYEXPRE__

#include "node.hpp"

class BinaryExpr : public Node {
    public:
        virtual ~BinaryExpr();
        
    protected:
        BinaryExpr(const Node& _n1, const Node& _n2);
        BinaryExpr(const Node* _n1, const Node* _n2);
        Node* n1, * n2;

    private:
        void remove_all();
};

#endif