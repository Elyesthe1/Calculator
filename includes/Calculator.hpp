#pragma once
#include "AST.hpp"
#include <iostream>
#include <exception>
class Calculator
{
    public:
        static void Start();
        static void MainLoop();
        static void ProcessInput(const std::string &Input);
        // static void IsTokenValid(const char &Token);
        // static bool IsParenthesis(const char &token);
        // static bool IsOperator(const char &token);

        static int BuildNumber();
        static void MooveSpace();

        static AST *ParseExpression();
        static AST *ParseTerm();
        static AST *ParseFactor();


        static std::string input;
        static std::size_t index;
};