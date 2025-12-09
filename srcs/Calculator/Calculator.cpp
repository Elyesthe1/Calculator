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
    const int signe = Calculator::input[Calculator::index] == '-' ? -1 : 1;
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
        {
            std::cerr << "Missing ')'" << std::endl;
            return NULL;
        }
        Calculator::index++; Calculator::MooveSpace();
        return node;
    }
    return NULL;
}


AST *Calculator::ParseTerm()
{
    AST *left = Calculator::ParseFactor();
    if (!left)
        return NULL;
    while(Calculator::input[Calculator::index] == '/' || Calculator::input[Calculator::index] == '*')
    {
        const char Operator = Calculator::input[Calculator::index];
        Calculator::index++; Calculator::MooveSpace();
        AST *right = ParseFactor();
        if (!right)
            return NULL;
        left = new AST(Operator, left, right);
    }
    return left;
}


AST *Calculator::ParseExpression()
{
    AST *left = Calculator::ParseTerm();
    if (!left)
        return NULL;
    while(Calculator::input[Calculator::index] == '+' || Calculator::input[Calculator::index] == '-')
    {
        const char Operator = Calculator::input[Calculator::index];
        Calculator::index++; Calculator::MooveSpace();

        AST *right = Calculator::ParseTerm();;
        if (!right)
            return NULL;

        left = new AST(Operator, left, right);
    }
    return left;
}

std::optional<int> Calculator::ProcessCalcul(AST *tree)
{
    if (!tree)
        return std::nullopt;
    
    if (tree->token == 'N')
        return tree->number;
    
    std::optional<int> left = Calculator::ProcessCalcul(tree->left);
    std::optional<int> right = Calculator::ProcessCalcul(tree->right);

    if (!left.has_value() || !right.has_value())
        return std::nullopt;

    switch (tree->token)
    {
        case '+': return left.value() + right.value();
        case '-': return left.value() - right.value();
        case '*': return left.value() * right.value();
        case '/': 
            if (right == 0)
            {
                std::cerr << "Division by zero" << std::endl; /// help sasso
                return std::nullopt;
            }
            return left.value() / right.value();
    }
    std::cerr << "Unknown operator" << std::endl; /// help sasso
    return std::nullopt;
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
    if(!tree)
        return ;
    std::optional<int> result = Calculator::ProcessCalcul(tree);
    if (!result)
    {
        Calculator::DeleteTree(tree);
        return ;
    }
    std::cout << "= "  << result.value() << std::endl;
    Calculator::DeleteTree(tree);
}
int Calculator::Compute(std::string expression)
{
    Calculator::input = expression;
    Calculator::index = 0;

    AST *tree = Calculator::ParseExpression();
    if(!tree)
        return 0;
    std::optional<int> result = Calculator::ProcessCalcul(tree);
    if (!result)
    {
        Calculator::DeleteTree(tree);
        return 0;
    }
    Calculator::DeleteTree(tree);
    return result.has_value() ? result.value() : 0;
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
        Calculator::ProcessInput(line);
    }
}