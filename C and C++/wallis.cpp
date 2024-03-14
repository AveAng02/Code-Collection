#include <iostream>
#include <cfloat>

int main()
{
    long double numerator = 1.0, denominator = 1.0;

    for(double i = 1; i < 500; i++)
        numerator *= 4 * i * i;

    for(double i = 1; i < 500; i++)
        denominator *= (2 * i - 1) * (2 * i + 1);

    std::cout << (2 * numerator) / denominator << std::endl;

    return 0;
}