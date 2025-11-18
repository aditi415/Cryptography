#ifndef POLLARD_RHO_RADDING_HPP
#define POLLARD_RHO_RADDING_HPP

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <vector>

using namespace NTL;
using namespace std;

// -------------------- DLP state & table entry --------------------
struct DLPState {
    ZZ x;   // current group element (mod p)
    ZZ a;   // exponent of g
    ZZ b;   // exponent of h
    DLPState() : x(ZZ(0)), a(ZZ(0)), b(ZZ(0)) {}
};

struct DLPTableEntry {
    ZZ mul;   // g^{alpha} * h^{beta} mod p
    ZZ alpha; // exponent for g
    ZZ beta;  // exponent for h
};

// -------------------- ECDLP point, state & table entry --------------------
struct ECPoint {
    ZZ_p x, y;
    bool inf;
    ECPoint() : x(ZZ_p::zero()), y(ZZ_p::zero()), inf(true) {}
    ECPoint(const ZZ_p &xx, const ZZ_p &yy) : x(xx), y(yy), inf(false) {}
};

struct ECState {
    ECPoint R; // current point
    ZZ a;      // coefficient for P
    ZZ b;      // coefficient for Q
    ECState() : R(), a(ZZ(0)), b(ZZ(0)) {}
};

struct ECTableEntry {
    ECPoint point; // alpha*P + beta*Q
    ZZ alpha;
    ZZ beta;
};

// -------------------- Elliptic curve (short Weierstrass) --------------------
struct EllipticCurve {
    ZZ_p a, b; // curve coefficients
    ZZ p;      // underlying prime

    EllipticCurve() {}
    EllipticCurve(const ZZ &aa, const ZZ &bb, const ZZ &pp);

    ECPoint add(const ECPoint &P, const ECPoint &Q) const;
    ECPoint dbl(const ECPoint &P) const;
    ECPoint mul(const ECPoint &P, const ZZ &k) const;
    ZZ coord_mod(const ECPoint &P, const ZZ &m) const;
};

// -------------------- Helpers --------------------
ZZ inv_mod_safe(const ZZ &a, const ZZ &m);

// -------------------- R-adding walk interfaces --------------------
// multiplicative DLP: solve g^x = h (mod p)
ZZ pollard_rho_radding_dlp(const ZZ &p, const ZZ &g, const ZZ &h, long r = 16, long max_iters = 0);

// ECDLP: solve Q = k*P on curve E with known order
ZZ pollard_rho_radding_ecdlp(const EllipticCurve &E, const ECPoint &P, const ECPoint &Q, const ZZ &order, long r = 16, long max_iters = 0);

#endif // POLLARD_RHO_RADDING_HPP

