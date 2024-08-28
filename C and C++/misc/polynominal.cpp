
#include <iostream>
#include <cmath>
#include <stack>

class Terms
{
public:
    Terms(float coefficient_ = 0,
          float exponent_ = 0)
        : exponent(exponent_),
          coefficient(coefficient_)
    {}

    void operator=(const Terms& term);
    float operator()(float x);

    float coefficient;
    float exponent;
};

class Polynomial
{
public:
    Polynomial(std::string expression_string)
    {
        init(expression_string);
    }

    void operator=(const Polynomial& term);
    
    // implementing the shunting yard algorithm
    float operator()(float x);

    void init(std::string str);

private:
    std::stack<Terms> termStack;
    std::stack<char> operatorStack;
};

float foo(float x)
{
    return 7 * std::pow(x, 3);
}

int main()
{
    float a = 0.0f;
    Terms term(7, 3);

    std::cout << "Polynomial 7x^3\n";
    std::cin >> a;

    float result = term(a);

    std::cout << "From foo function = " << foo(a)
    << "\nFrom the Terms class = " << result << std::endl;

    return 0;
}

void Terms::operator=(const Terms& term)
{
    coefficient = term.coefficient;
    exponent = term.exponent;
}

float Terms::operator()(float x)
{
    return coefficient * std::pow(x, exponent);
}
