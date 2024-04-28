#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int powerModulo(int a, int b, int m) {
    int result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        b = b / 2;
        a = (a * a) % m;
    }
    return result;
}

int multiplicativeInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

int generateRandomNumber(int q) {
    return rand() % (q - 1) + 1;
}

struct Signature {
    int r;
    int s;
    int y;
    Signature(int r, int s, int y) : r(r), s(s), y(y) {}
};

Signature sign(int p, int q, int h, int md, int a) {
    srand(time(0));
    int k = generateRandomNumber(q);
    int g = powerModulo(h, (p - 1) / q, p);
    int x = a;
    int y = powerModulo(g, x, p);
    int r = powerModulo(g, k, p) % q;
    int s = (multiplicativeInverse(k, q) * (md + x * r)) % q;
    cout << "Intermediate Values for Signing:\n";
    cout << "g: " << g << "\n";
    cout << "x (private key): " << x << "\n";
    cout << "y (public key): " << y << "\n";
    cout << "k: " << k << "\n";
    cout << "r: " << r << "\n";
    cout << "s: " << s << "\n";
    return Signature(r, s, y);
}

bool verify(int p, int q, int h, int md, int y, int r, int s) {
    int g = powerModulo(h, (p - 1) / q, p);
    int w = multiplicativeInverse(s, q);
    int u1 = (md * w) % q;
    int u2 = (r * w) % q;
    int v = ((powerModulo(g, u1, p) * powerModulo(y, u2, p)) % p) % q;
    cout << "\nIntermediate Values for Verification:\n";
    cout << "g: " << g << "\n";
    cout << "y (public key): " << y << "\n";
    cout << "r: " << r << "\n";
    cout << "s: " << s << "\n";
    cout << "w: " << w << "\n";
    cout << "u1: " << u1 << "\n";
    cout << "u2: " << u2 << "\n";
    cout << "v: " << v << "\n";
    return v == r;
}

int main() {
    int p, q, h, md, a;
    cout << "Enter prime number p: ";
    cin >> p;
    cout << "Enter prime number q: ";
    cin >> q;
    cout << "Enter primitive root h: ";
    cin >> h;
    cout << "Enter message digest md: ";
    cin >> md;
    cout << "Enter private key a: ";
    cin >> a;
    Signature signature = sign(p, q, h, md, a);
    if (verify(p, q, h, md, signature.y, signature.r, signature.s)) {
        cout << "\nSignature verified\n";
    } else {
        cout << "\nSignature not verified\n";
    }
    return 0;
}
