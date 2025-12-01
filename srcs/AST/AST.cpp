#include "../../includes/AST.hpp"
#include <iostream>

AST::AST(const int number): token('N'), number(number) {}
AST::AST(const char token, AST *left, AST *right):  token(token), number(0), left(left), right(right)  {}