#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/Random.h>
#include "radd.hpp"

using namespace std;
using namespace NTL;

int main() {
    cout << "Pollard R-adding walk\n\n";
    cout << "DLP\n";
    ZZ p = conv<ZZ>(1000003);
    ZZ_p::init(p);

    ZZ g = conv<ZZ>(2);
    ZZ x_real = conv<ZZ>(12345);
    ZZ h = PowerMod(g, x_real, p);

    cout << "p = " << p << "\n";
    cout << "g = " << g << "\n";
    cout << "real x = " << x_real << "\n";

    long r = 16;
    ZZ x_found = pollard_rho_radding_dlp(p, g, h, r, 0);

    if (x_found >= 0) cout << "found x = " << x_found << "\n";
    else cout << "failure to recover x\n";
    cout << "\n";

    return 0;
}

