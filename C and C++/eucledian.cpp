#include <bits/stdc++.h>
using namespace std;

int euclidean_algorithm(int a, int b) {
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;

    cout << "Enter the first integer: ";
    cin >> num1;

    cout << "Enter the second integer: ";
    cin >> num2;

    int gcd = euclidean_algorithm(num1, num2);
    cout << "GCD of " << num1 << " and " << num2 << " is: " << gcd << std::endl;
    return 0;
}
