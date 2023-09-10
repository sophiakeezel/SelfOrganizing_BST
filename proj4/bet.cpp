// Sophia Keezel, Project 4: Binary Tree and Its Application, COP4530, 11/10/2022

#include <iostream>
#include <stack>
#include "bet.h"

using namespace std;

// default zero-parameter constructor
BET::BET() {
    root = new BinaryNode;
}

// one-parameter constructor, where parameter "postfix" is string containing a postfix expression
BET::BET(const string postfix) {
    root = new BinaryNode;
    buildFromPostfix(postfix);
}

// copy constructor
BET::BET(const BET & rhs) {
    root = clone(rhs.root);
}

// destructor
BET::~BET() {
    makeEmpty(root);
}

// return true if the new tree is built successfully. Return false if an error is encountered.
bool BET::buildFromPostfix(const string postfix) {

    // variable token which contains characters of postfix expression
    string token;

    // declare a stack
    stack<BinaryNode*> stk;
    stringstream ss(postfix);

    // variables which keep track of operands and operators
    int a = 0;
    int b = 0;

    // string postfix contains no characters
    if (postfix.empty()) {
        root = nullptr;
        return false;
    }

    // ensure tree is empty
    if (!empty()) {
        makeEmpty(root);
    }

    // while not end of postfix expression
    while (ss >> token) {

        // create a new node
        auto *temp = new BinaryNode(token);

        // if is an operand, push into the stack
        if (isOperand(token)) {
            a++;
            stk.push(temp);    // push new to end of Stack
        } else if (Precedence(token) != 0) // if an operator
        {
            b++;
            if (a == b) {
                root = nullptr;
                return false;
            } else {
                // pop operands from the stack and add as children for the operator
                temp->right = stk.top();
                stk.pop();
                temp->left = stk.top();
                stk.pop();
                // push new node into stack
                stk.push(temp);
            }
        }
    }

    // top of the stack is the final bet
    if (a != b)
        root = stk.top();

    if (stk.empty()) {
        root = nullptr;
        return false;
    }

    return true;
}


// assignment operator
const BET &BET::operator=(const BET &b) {
    root = clone(b.root);
    return *this;
}


// print out the infix expression
void BET::printInfixExpression() {
    printInfixExpression(root);
    cout << endl;
}

// print the postfix form of the expression
void BET::printPostfixExpression() {
    printPostfixExpression(root);
    cout << endl;
}

// return the number of nodes in the tree
size_t BET::size() {
    return size(root);
}

// return the number of leaf nodes in the tree
size_t BET::leaf_nodes() {
    return leaf_nodes(root);
}

// return true if the tree is empty
bool BET::empty() {
    if (root == nullptr)
        return true;
    else
        return false;
}

// print to the standard output the corresponding infix expression
void BET::printInfixExpression(BinaryNode *n) {

    bool check = false;

    // if tree is empty
    if (n == nullptr)
        cout << "empty tree";
    else {
        // if element contains a left child
        if (n->left != nullptr) {
            // check if left element is an operator and contains a smaller precedence than element n
            if (isOperator(n->left->element) && (Precedence(n->element) > Precedence(n->left->element))) {
                cout << "( ";
                check = true;
            }

            // recursively call printInfixExpression with the left child of element n
            printInfixExpression(n->left);

            // if open parenthesis exists
            if (check) {
                cout << ") ";
                check = false;
            }

            // print element
            cout << n->element << " ";

            // check if right element is an operator and contains a smaller precedence than element n
            if (isOperator(n->right->element) && (Precedence(n->element) >= Precedence(n->right->element))) {
                cout << "( ";
                check = true;
            }

            // recursively call printInfixExpression with the right child of element n
            printInfixExpression(n->right);

            // check if open parenthesis exists
            if (check) {
                cout << ") ";
                check = false;
            }

        } else // if left child doesn't exist
            cout << n->element << " ";
    }
}

// print to the standard output the corresponding postfix expression.
void BET::printPostfixExpression(BinaryNode *n) {

    // if tree is empty
    if (n == nullptr)
        cout << "empty tree";
    // recursively call printPostfixExpression until element doesn't have a left child
    else {
        if (n->left != nullptr) {
            printPostfixExpression(n->left);
            printPostfixExpression(n->right);
            cout << n->element << " ";
        } else
            cout << n->element << " ";
    }
}

// delete all nodes in the subtree pointed to by t.
void BET::makeEmpty(BinaryNode *&t) {
    // if node is != empty
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);

        delete t;
    }
    t = nullptr;
}

// clone all nodes in the subtree pointed to by t
BET::BinaryNode *BET::clone(BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    } else
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

// return the number of nodes in the subtree pointed to by t
size_t BET::size(BET::BinaryNode *t) {
    if (t == nullptr)
        return 0;
    else
        return (1 + size(t->left) + size(t->right));
}

// return the number of leaf nodes in the subtree pointed to by t
size_t BET::leaf_nodes(BET::BinaryNode *t) {
    if (t == nullptr)
        return 0;
    //if node has no child
    if (t->left == nullptr && t->right == nullptr)
        return 1;
    else
        return leaf_nodes(t->left) + leaf_nodes(t->right);
}

// function to check for operands
bool BET::isOperand(const string s) {
    for (int i = 0; i < int(s.size()); i++)
        // if is a num
        if (isalnum(s[i]) == false)
            return false;
    return true;
}

// function to check for operators precedence
int BET::Precedence(const string s) {
    if (s == "(" || s == ")") // highest precedence
        return (3);
    else if (s == "*" || s == "/")
        return (2);
    else if (s == "+" || s == "-") // lowest precedence
        return (1);
    else
        return 0;
}

// function to check string for operators
bool BET::isOperator(const string s) {
    return (s == "+" || s == "-" || s == "/" || s == "*");
}
