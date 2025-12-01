#include "../../includes/Calculator.hpp"

std::string Calculator::input;
std::size_t Calculator::index = 0;

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
    Calculator::MooveSpace();
    if (std::isdigit(Calculator::input[Calculator::index]) || ((Calculator::input[Calculator::index] == '-' || Calculator::input[Calculator::index] == '+') && std::isdigit(Calculator::input[Calculator::index + 1])) )
        return new AST(Calculator::BuildNumber());
    if(Calculator::input[Calculator::index] == '(')
    {
        Calculator::index++; Calculator::MooveSpace();
        AST *node = Calculator::ParseExpression();
        if (Calculator::input[Calculator::index] != ')')
            throw std::logic_error("Missing ')'");
        Calculator::index++; Calculator::MooveSpace();
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

        AST *right = Calculator::ParseTerm();;

        left = new AST(Operator, left, right);
    }
    return left;
}

int Calculator::ProcessCalcul(AST *tree)
{
    if (!tree)
        return 0;
    
    if (tree->token == 'N')
        return tree->number;
    
    int left = Calculator::ProcessCalcul(tree->left);
    int right = Calculator::ProcessCalcul(tree->right);

    switch (tree->token)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': 
            if (right == 0)
                throw std::domain_error("Division by zero");
            return left / right;
    }
    throw std::logic_error("Unknown operator");
}

void Calculator::DeleteTree(AST *tree)
{
    if (!tree)
        return;
    Calculator::DeleteTree(tree->left);
    Calculator::DeleteTree(tree->right);
    delete tree;
}


void Calculator::ProcessInput(const std::string &line)
{
    Calculator::input = line;
    Calculator::index = 0;
    AST *tree = Calculator::ParseExpression();
    int result = Calculator::ProcessCalcul(tree);
    std::cout << "= "  << result << std::endl;
    Calculator::DeleteTree(tree);
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