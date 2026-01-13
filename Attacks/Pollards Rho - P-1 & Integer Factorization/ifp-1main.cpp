#include <iostream>
#include <NTL/ZZ.h>
#include "ifp-1.hpp"
using namespace std;
using namespace NTL;

int main() {
    ZZ n = ZZ(143);  

    cout << "Number: " << n << "\n";

    Pollard P(n);

    ZZ r1 = P.pollardRho();
    if (r1 == 1)
        cout << "Pollard Rho failed.\n";
    else
        cout << "Pollard Rho factor: " << r1 << " and " << n / r1 << "\n";

    ZZ r2 = P.pollardPMinus1();
    if (r2 == 1)
        cout << "Pollard p-1 failed.\n";
    else
        cout << "Pollard p-1 factor: " << r2 << " and " << n / r2 << "\n";

    return 0;
}

