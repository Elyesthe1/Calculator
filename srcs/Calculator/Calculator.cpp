#include "../../includes/Calculator.hpp"

std::string Calculator::input;
std::size_t Calculator::index = 0;

// bool Calculator::IsParenthesis(const char &token) 
// {
//     if (token == '(' || token == ')') 
//         return 1;
//     return 0;
// }

// bool Calculator::IsOperator(const char &token) 
// {
//     if (token == '+' || token == '/' || token == '-' || token == '*')
//         return 1; 
//     return 0;

// }

// void Calculator::IsTokenValid(const char &Token)
// {
//     if (!std::isdigit(Token) && !std::isspace(Token) && !Calculator::IsOperator(Token) && !Calculator::IsParenthesis(Token))
//         throw std::logic_error(std::string("Unexpected token: '") + Token + "'");
// }

void Calculator::MooveSpace() 
{
    while(std::isspace(Calculator::input[Calculator::index])) 
        Calculator::index++;
}


int Calculator::BuildNumber()
{
    Calculator::MooveSpace();
    int result = 0;
    int signe = Calculator::input[Calculator::index] == '-' ? -1 : 1;
    if (Calculator::input[Calculator::index] == '-' || Calculator::input[Calculator::index] == '+')
        Calculator::index++;
    for(; std::isdigit(Calculator::input[Calculator::index]); Calculator::index++)
        result = result * 10 + (Calculator::input[Calculator::index] - '0');
    Calculator::MooveSpace();
    return result * signe;
}


AST *Calculator::ParseFactor()
{
    if (std::isdigit(Calculator::input[Calculator::index]) || ((Calculator::input[Calculator::index] == '-' || Calculator::input[Calculator::index] == '+') && std::isdigit(Calculator::input[Calculator::index + 1])) )
        return new AST(Calculator::BuildNumber());
    if(Calculator::input[Calculator::index] == '(')
    {
        Calculator::index++; Calculator::MooveSpace();
        AST *node = Calculator::ParseExpression();
        if (Calculator::input[Calculator::index] != ')')
            throw std::logic_error("Missing ')'");
        Calculator::index++;
        return node;
        
    }
    throw std::logic_error("Bad factor");
}


AST *Calculator::ParseTerm()
{
    AST *left = Calculator::ParseFactor();
    while(Calculator::input[Calculator::index] == '/' || Calculator::input[Calculator::index] == '*')
    {
        const char Operator = Calculator::input[Calculator::index];
        Calculator::index++; Calculator::MooveSpace();
        AST *right = ParseFactor();
        left = new AST(Operator, left, right);
    }

    return left;
}


AST *Calculator::ParseExpression()
{
    AST *left = Calculator::ParseTerm();

    while(Calculator::input[Calculator::index] == '+' || Calculator::input[Calculator::index] == '-')
    {
        const char Operator = Calculator::input[Calculator::index];
        Calculator::index++; Calculator::MooveSpace();

        AST *right = ParseFactor();

        left = new AST(Operator, left, right);
    }
    return left;
}

void Calculator::ProcessInput(const std::string &line)
{
    Calculator::input = line;
    Calculator::index = 0;
    AST *tree = Calculator::ParseExpression();
    // faire mes truc puis
    delete tree;
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