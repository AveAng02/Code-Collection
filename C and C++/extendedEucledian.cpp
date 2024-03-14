#include <iostream>
using namespace std;

void extendedEuclidean(int a, int b, int &gcd, int &x, int &y) {
    if (b == 0) {
        gcd = a;
        x = 1;
        y = 0;
    } else {
        int temp_gcd, temp_x, temp_y;
        extendedEuclidean(b, a % b, temp_gcd, temp_x, temp_y);
        gcd = temp_gcd;
        x = temp_y;
        y = temp_x - (a / b) * temp_y;
    }
}

int main() {
    int num1, num2;
    int gcd, x, y;

    cout << "Enter the first integer: ";
    cin >> num1;

    cout << "Enter the second integer: ";
    cin >> num2;

    extendedEuclidean(num1, num2, gcd, x, y);
    cout << "Extended GCD of " << num1 << " and " << num2 << " is: " << gcd << endl;
    cout << "Coefficients (x, y) such that ax + by = gcd(a, b): (" << x << ", " << y << ")" << endl;

    return 0;
}


