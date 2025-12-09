#pragma once
#include "AST.hpp"
#include <iostream>
#include <exception>
class Calculator
{
    public:
        static void Start();
        static int Compute(std::string expression);
        static void MainLoop();
        static void ProcessInput(const std::string &Input);

        static int BuildNumber();
        static std::optional<int> ProcessCalcul(AST *tree);
        static void MooveSpace();
        static void DeleteTree(AST *tree);

        static AST *ParseExpression();
        static AST *ParseTerm();
        static AST *ParseFactor();


        static std::string input;
        static std::size_t index;
};