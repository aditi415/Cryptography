#include <iostream>
#include "pollards.hpp"

int main() {
    Pollard P;

    std::cout << " DLP\n";
    long long p = 97;
    long long g = 5;
    long long secret_x = 10;
    long long h = 1;
    for (int i = 0; i < secret_x; ++i) h = (h * g) % p;

    long long recovered = P.DLP(p, g, h);
    std::cout << "secret x = " << secret_x << ", recovered = " << recovered << "\n\n";

    std::cout << "ECDLP\n";
    long long a = 2;
    long long b = 3;
    long long Px = 3, Py = 6;       
    long long k = 5;               
    long long Qx = Px, Qy = Py;
    Pollard::Point cur = {Px, Py};
    for (int i = 1; i < k; ++i) {
    }
    long long Qx_d = 80; 
    long long Qy_d = 10;

    long long recovered_k = P.ECDLP(p, a, b, Px, Py, Qx_d, Qy_d);
    std::cout << "secret k = " << k << ", recovered = " << recovered_k << "\n";

    return 0;
}

