#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#ifndef BET_H
#define BET_H

class BET {
public:
    // nested structure which contains node related information
    struct BinaryNode {
        string element;
        BinaryNode* left; 		// pointer to left child
        BinaryNode* right; 		// pointer to right child
        BinaryNode(const string & e = string{}, BinaryNode* l = nullptr, BinaryNode* r = nullptr) : element{ e }, left{ l }, right{ r } {}
    };

    BET();
    BET(const string postfix);
    BET(const BET & rhs);
    ~BET();
    bool buildFromPostfix(const string postfix);
    const BET & operator= (const BET &b);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();

private:
    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t) const;
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);
    BinaryNode * root;
    int Precedence(const string s);
    bool isOperator(const string s);
    bool isOperand(const string s);

};

#endif
