#include "../../includes/Calculator.hpp"

bool Calculator::IsParenthesis(const char &token) {if (token == '(' || token == ')') return 1; return 0;}
bool Calculator::IsOperator(const char &token) {if (token == '+' || token == '/' || token == '-' || token == '*')return 1; return 0;}

void Calculator::IsTokenValid(const char &Token)
{
    if (!std::isdigit(Token) && !std::isspace(Token) && !Calculator::IsOperator(Token) && !Calculator::IsParenthesis(Token))
        throw std::logic_error(std::string("Unexpected token: '") + Token + "'");
}


void Calculator::ProcessInput(const std::string &line)
{
   for(int i = 0; i < line.size(); i++)
   {
        Calculator::IsTokenValid(line[i]);
   }
}

void Calculator::Start()
{
    Calculator::MainLoop();
}

void Calculator::MainLoop()
{
    while(1)
    {
        std::cout << "calc> ";
        std::string line;
        if (!std::getline(std::cin, line))
            break;
        try
        {
            Calculator::ProcessInput(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        
    }
}