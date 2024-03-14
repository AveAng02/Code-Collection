#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Divides divident by divisor and loads the result in the value vector.
void division(std::vector<uint32_t>& value, uint64_t divident_, uint64_t divisor_, uint64_t precision);

// Adds vector a and b and loads the result in the value vector.
void sum(std::vector<uint32_t>& value, std::vector<uint32_t>& a, std::vector<uint32_t>& b, uint32_t precision);

// implements the arctan method to calculate pi.
void arctanMethod(std::vector<uint32_t>& value, uint32_t precision);

// Utility function for calculating 2nCn
long long twoNCN(long long n);


int main(int argc, char** argv)
{
    int precision = std::stoi(argv[1]);

    std::vector<uint32_t> value (precision, 0);

    arctanMethod(value, precision);
    
    for(auto i : value)
        std::cout << i;

    std::cout << "\n";

    return 0;
}


void division(std::vector<uint32_t>& value, uint64_t divident_, uint64_t divisor_, uint64_t precision)
{ 
    int remainder = 0, divisor = divisor_, divident = divident_;

    for(int i = 0; i < precision; i++)
    {
        remainder = divident % divisor;
        value[i] = divident / divisor;
        divident = remainder * 10;
    }
}


void sum(std::vector<uint32_t>& value, std::vector<uint32_t>& a, std::vector<uint32_t>& b, uint32_t precision)
{
    uint32_t carry = 0, sum = 0;

    for(int i = precision - 1; i >= 0; i--)
    {
        sum = a[i] + b[i] + carry;
        carry = sum / 10;
        sum = sum % 10;
        value[i] = sum;
    }
}


void arctanMethod(std::vector<uint32_t>& value, uint32_t precision)
{
    long long numerator = 2, denominator = 1, nextOdd = 1;

    std::vector<uint32_t> divValue (precision, 0);

    for(int i = 1; i <= precision; i++)
    {
        division(divValue, numerator, denominator, precision);
        
        sum(value, value, divValue, precision);

        std::cout << numerator << " " << denominator << std::endl;

        nextOdd += 2;
        denominator = twoNCN(i) * nextOdd;
        numerator = pow(2, i + 1);

        while(denominator % 2 != 1 && numerator > 2)
        {
            denominator /= 2;
            numerator /= 2;
        }
    }
}


long long twoNCN(long long n)
{
    long long value = 1, twoN = 2 * n, fact2N = 1, factN = 1;

    for(int i = 1; i <= twoN; i++)
        fact2N *= i;

    for(int i = 1; i <= n; i++)
        factN *= i;

    value = fact2N / (factN * factN);

    return value;
}

