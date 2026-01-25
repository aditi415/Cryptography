#include "radd.hpp"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/Random.h>

#include <iostream>

using namespace NTL;
using namespace std;

ZZ pollard_rho_radding_dlp(const ZZ &p, const ZZ &g, const ZZ &h, long r, long max_iters) {
    if (r < 2) r = 2;
    ZZ order = p - 1;
    
    vector<DLPTableEntry> table;
    table.reserve(r);
    for (long j = 0; j < r; ++j) {
        DLPTableEntry e;
        e.alpha = conv<ZZ>(j + 1);      
        e.beta  = conv<ZZ>(j);         
        ZZ aPow = PowerMod(g, e.alpha, p);
        ZZ bPow = PowerMod(h, e.beta, p);
        e.mul = MulMod(aPow, bPow, p);
        table.push_back(e);
    }
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
            if (PowerMod(g, x, p) == h) return x;
            else return ZZ(-1);
        }
    }
    return ZZ(-1);
}

