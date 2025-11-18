#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/Random.h>
#include "radd.hpp"

using namespace std;
using namespace NTL;

int main() {
    cout << "Pollard R-adding walk demo (Option A table)\n\n";

    // ------------------ DLP demo ------------------
    cout << "[DLP demo]\n";
    ZZ p = conv<ZZ>(1000003); // prime
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

    // ------------------ ECDLP demo ------------------
    cout << "[ECDLP demo]\n";
    ZZ p_ec = conv<ZZ>(10007);
    ZZ_p::init(p_ec);

    // small example curve: y^2 = x^3 + a*x + b  (make sure point lies on curve)
    ZZ a = conv<ZZ>(2);
    ZZ b = conv<ZZ>(3);
    EllipticCurve E(a, b, p_ec);

    // choose base point P (small example) - ensure valid
    ECPoint P(conv<ZZ_p>(5), conv<ZZ_p>(1));

    // choose small order for demo (not actual curve order). For correctness in demo, pick small scalar space
    ZZ order = conv<ZZ>(1000); // for demo only

    ZZ k_real = conv<ZZ>(123);
    ECPoint Q = E.mul(P, k_real);

    cout << "curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p_ec << ")\n";
    cout << "P = (" << rep(P.x) << ", " << rep(P.y) << ")\n";
    cout << "real k = " << k_real << "\n";

    ZZ k_found = pollard_rho_radding_ecdlp(E, P, Q, order, r, 0);
    if (k_found >= 0) cout << "found k = " << k_found << "\n";
    else cout << "failure to recover k\n";

    return 0;
}

