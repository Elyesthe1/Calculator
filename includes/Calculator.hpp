#pragma once
#include <iostream>
#include <exception>
class Calculator
{
    public:
        static void Start();
        static void MainLoop();
        static void ProcessInput(const std::string &Input);
        static void IsTokenValid(const char &Token);
        static bool IsParenthesis(const char &token);
        static bool IsOperator(const char &token);
};