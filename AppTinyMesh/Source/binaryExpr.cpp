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
    delete n1;
    delete n2;
}