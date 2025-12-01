#pragma once

struct AST
{
    public:
        AST(const int number);
        AST(const char token, AST *left, AST *right);
        const char token;
        const int number;
        AST *left;
        AST *right;
};