#include "binaryExpr.hpp"

BinaryExpr::~BinaryExpr() {
            remove_all();
}

BinaryExpr::BinaryExpr(const Node& _n1, const Node& _n2) :
    n1(_n1.clone()),
    n2(_n2.clone())
{}

BinaryExpr::BinaryExpr(const Node* _n1, const Node* _n2) :
    n1(_n1->clone()),
    n2(_n2->clone())
{}

void BinaryExpr::remove_all() {
    if (typeid(n1).name() == typeid(BinaryExpr).name()) {
        dynamic_cast<BinaryExpr*>(n1)->remove_all();
    }
    delete n1;
    if (typeid(n2).name() == typeid(BinaryExpr).name()) {
        dynamic_cast<BinaryExpr*>(n2)->remove_all();
    }
    delete n2;
}