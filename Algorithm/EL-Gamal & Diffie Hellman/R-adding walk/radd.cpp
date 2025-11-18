#include "radd.hpp"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/Random.h>
#include <iostream>

using namespace NTL;
using namespace std;

// -------------------- EllipticCurve methods --------------------
EllipticCurve::EllipticCurve(const ZZ &aa, const ZZ &bb, const ZZ &pp) {
    p = pp;
    ZZ_p::init(pp);
    a = conv<ZZ_p>(aa % pp);
    b = conv<ZZ_p>(bb % pp);
}

// point addition (handles infinities)
ECPoint EllipticCurve::add(const ECPoint &P, const ECPoint &Q) const {
    if (P.inf) return Q;
    if (Q.inf) return P;

    if (P.x == Q.x) {
        // P == -Q ?
        if (P.y + Q.y == ZZ_p::zero()) return ECPoint();
        // tangent (point doubling)
        return dbl(P);
    } else {
        ZZ_p lambda = (Q.y - P.y) * inv(Q.x - P.x);
        ZZ_p xr = lambda * lambda - P.x - Q.x;
        ZZ_p yr = lambda * (P.x - xr) - P.y;
        return ECPoint(xr, yr);
    }
}

ECPoint EllipticCurve::dbl(const ECPoint &P) const {
    if (P.inf) return P;
    ZZ_p denom = P.y + P.y;
    if (denom == ZZ_p::zero()) return ECPoint(); // infinity
    ZZ_p lambda = (3 * P.x * P.x + a) * inv(denom);
    ZZ_p xr = lambda * lambda - P.x - P.x;
    ZZ_p yr = lambda * (P.x - xr) - P.y;
    return ECPoint(xr, yr);
}

ECPoint EllipticCurve::mul(const ECPoint &P, const ZZ &k) const {
    ECPoint R; // infinity
    ECPoint A = P;
    ZZ kk = k;
    while (kk > 0) {
        if (bit(kk, 0)) R = add(R, A);
        A = dbl(A);
        kk >>= 1;
    }
    return R;
}

ZZ EllipticCurve::coord_mod(const ECPoint &P, const ZZ &m) const {
    if (P.inf) return ZZ(0);
    ZZ rx = rep(P.x);
    if (m == 0) return rx;
    return rx % m;
}

// -------------------- Helpers --------------------
ZZ inv_mod_safe(const ZZ &a, const ZZ &m) {
    ZZ x, y;
    ZZ g = XGCD(x, y, a, m);
    if (g != 1) return ZZ(0);
    ZZ r = x % m;
    if (r < 0) r += m;
    return r;
}

// -------------------- DLP: R-adding walk --------------------
ZZ pollard_rho_radding_dlp(const ZZ &p, const ZZ &g, const ZZ &h, long r, long max_iters) {
    if (r < 2) r = 2;
    ZZ order = p - 1;

    // Build simple Option A table: alpha = j+1, beta = j (small multipliers)
    vector<DLPTableEntry> table;
    table.reserve(r);
    for (long j = 0; j < r; ++j) {
        DLPTableEntry e;
        e.alpha = conv<ZZ>(j + 1);      // 1,2,3,...
        e.beta  = conv<ZZ>(j);          // 0,1,2,...
        ZZ aPow = PowerMod(g, e.alpha, p);
        ZZ bPow = PowerMod(h, e.beta, p);
        e.mul = MulMod(aPow, bPow, p);
        table.push_back(e);
    }

    // random start
    ZZ a0 = RandomBnd(order);
    ZZ b0 = RandomBnd(order);
    ZZ x0 = MulMod(PowerMod(g, a0, p), PowerMod(h, b0, p), p);

    DLPState tort; tort.x = x0; tort.a = a0; tort.b = b0;
    DLPState hare = tort;

    long iter = 0;
    auto step = [&](DLPState &s) {
        long idx = conv<long>(s.x % r);
        s.x = MulMod(s.x, table[idx].mul, p);
        s.a = (s.a + table[idx].alpha) % order;
        s.b = (s.b + table[idx].beta)  % order;
    };

    while (true) {
        if (max_iters && ++iter > max_iters) return ZZ(-1);
        step(tort);
        step(hare);
        step(hare);

        if (tort.x == hare.x) {
            ZZ num = (tort.a - hare.a) % order; if (num < 0) num += order;
            ZZ den = (hare.b - tort.b) % order; if (den < 0) den += order;
            if (den == 0) return ZZ(-1);
            ZZ inv = inv_mod_safe(den, order);
            if (inv == 0) return ZZ(-1);
            ZZ x = MulMod(num, inv, order);
            // verify
            if (PowerMod(g, x, p) == h) return x;
            else return ZZ(-1);
        }
    }
    return ZZ(-1);
}

// -------------------- ECDLP: R-adding walk --------------------
ZZ pollard_rho_radding_ecdlp(const EllipticCurve &E, const ECPoint &P, const ECPoint &Q, const ZZ &order, long r, long max_iters) {
    if (r < 2) r = 2;

    // Build Option A table: alpha = j+1, beta = j
    vector<ECTableEntry> table;
    table.reserve(r);
    for (long j = 0; j < r; ++j) {
        ECTableEntry e;
        e.alpha = conv<ZZ>(j + 1);
        e.beta  = conv<ZZ>(j);
        ECPoint aP = E.mul(P, e.alpha);
        ECPoint bQ = E.mul(Q, e.beta);
        e.point = E.add(aP, bQ);
        table.push_back(e);
    }

    // random start
    ZZ a0 = RandomBnd(order);
    ZZ b0 = RandomBnd(order);
    ECPoint R0 = E.add(E.mul(P, a0), E.mul(Q, b0));

    ECState tort; tort.R = R0; tort.a = a0; tort.b = b0;
    ECState hare = tort;

    long iter = 0;
    auto ec_step = [&](ECState &s) {
        ZZ idxZ = E.coord_mod(s.R, conv<ZZ>(r));
        long idx = conv<long>(idxZ);
        // update
        s.R = E.add(s.R, table[idx].point);
        s.a = (s.a + table[idx].alpha) % order;
        s.b = (s.b + table[idx].beta)  % order;
    };

    while (true) {
        if (max_iters && ++iter > max_iters) return ZZ(-1);
        ec_step(tort);
        ec_step(hare);
        ec_step(hare);

        ECPoint Rt = tort.R;
        ECPoint Rh = hare.R;
        if (!Rt.inf && !Rh.inf && Rt.x == Rh.x && Rt.y == Rh.y) {
            ZZ num = (tort.a - hare.a) % order; if (num < 0) num += order;
            ZZ den = (hare.b - tort.b) % order; if (den < 0) den += order;
            if (den == 0) return ZZ(-1);
            ZZ inv = inv_mod_safe(den, order);
            if (inv == 0) return ZZ(-1);
            ZZ k = MulMod(num, inv, order);
            // verify Q == k*P
            ECPoint K = E.mul(P, k);
            if (!K.inf && K.x == Q.x && K.y == Q.y) return k;
            else return ZZ(-1);
        }
    }
    return ZZ(-1);
}

