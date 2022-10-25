#include <iostream>

int main()
{
    int m = 0, n = 0, gcd = 0;

    std::cout << "Enter two integers:\n";
    std::cin >> m;
    std::cin >> n;

    while(n != 0)
    {
        gcd = n;
        n = (int)m%n;
        m = gcd;
    }

    std::cout << gcd << std::endl;
}