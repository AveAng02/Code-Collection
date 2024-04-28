#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate (a^b) % mod
long long power(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// Function to check if a number is prime
bool isPrime(long long num) {
    if (num <= 1)
        return false;
    if (num <= 3)
        return true;
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to generate a random prime number
long long generatePrime() {
    long long num;
    do {
        num = rand() % 100 + 50; // Adjust range as needed
    } while (!isPrime(num));
    return num;
}

// Function to generate public and private keys
void generateKeys(long long& e, long long& d, long long& n) {
    long long p = generatePrime();
    long long q = generatePrime();
    n = p * q;
    long long phi = (p - 1) * (q - 1);
    do {
        e = rand() % (phi - 2) + 2; // 1 < e < phi and gcd(e,phi) = 1
    } while (gcd(e, phi) != 1);
    // Calculate d such that (d * e) % phi = 1
    d = 1;
    while (((d * e) % phi) != 1) {
        d++;
    }
}

// Function to encrypt a message
long long encrypt(long long msg, long long e, long long n) {
    return power(msg, e, n);
}

// Function to decrypt a message
long long decrypt(long long encryptedMsg, long long d, long long n) {
    return power(encryptedMsg, d, n);
}

int main() {
    long long e, d, n;
    generateKeys(e, d, n);

    long long msg;
    cout << "Enter the message to be encrypted: ";
    cin >> msg;

    long long encryptedMsg = encrypt(msg, e, n);
    cout << "Encrypted message: " << encryptedMsg << endl;

    long long decryptedMsg = decrypt(encryptedMsg, d, n);
    cout << "Decrypted message: " << decryptedMsg << endl;

    return 0;
}
