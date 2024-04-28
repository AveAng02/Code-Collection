#include <iostream>
#include <cmath>

// Function to calculate power in modular arithmetic
long long power(long long base, long long exp, long long mod) {
    if (exp == 0) return 1;
    long long half = power(base, exp / 2, mod) % mod;
    long long result = (half * half) % mod;
    if (exp % 2 == 1) result = (result * base) % mod;
    return result;
}

// Function to generate a random prime number
long long generatePrime(int bits) {
    long long num = rand() % static_cast<int>(pow(2, bits)) + static_cast<int>(pow(2, bits - 1));
    while (true) {
        bool isPrime = true;
        for (int i = 2; i <= sqrt(num); ++i) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) return num;
        else num++;
    }
}

// Function to perform Diffie-Hellman key exchange
void diffieHellmanKeyExchange() {
    // Publicly known parameters
    const int bits = 16;
    long long p = generatePrime(bits); // Prime number
    long long g = 2; // Primitive root modulo p

    // Alice's private key
    long long a = rand() % (p - 1) + 1;
    // Alice's public key
    long long A = power(g, a, p);

    // Bob's private key
    long long b = rand() % (p - 1) + 1;
    // Bob's public key
    long long B = power(g, b, p);

    // Shared secret key computation
    long long secretKeyA = power(B, a, p);
    long long secretKeyB = power(A, b, p);

    std::cout << "Prime (p): " << p << std::endl;
    std::cout << "Primitive root (g): " << g << std::endl;
    std::cout << "Alice's private key (a): " << a << std::endl;
    std::cout << "Bob's private key (b): " << b << std::endl;
    std::cout << "Alice's public key (A): " << A << std::endl;
    std::cout << "Bob's public key (B): " << B << std::endl;
    std::cout << "Shared secret key computed by Alice: " << secretKeyA << std::endl;
    std::cout << "Shared secret key computed by Bob: " << secretKeyB << std::endl;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    diffieHellmanKeyExchange();

    return 0;
}
