#include "ifp-1.hpp"
#include <NTL/ZZ.h
using namespace NTL;

Pollard::Pollard(const ZZ& num) {
    n = num;
}

ZZ Pollard::gcdZZ(const ZZ &a, const ZZ &b) {
    return GCD(a, b);
}

ZZ Pollard::f(const ZZ &x) {
    return (x * x + 1) % n;
}

ZZ Pollard::pollardRho() {
    if (n % 2 == 0) return ZZ(2);

    ZZ x = ZZ(2);
    ZZ y = ZZ(2);
    ZZ d = ZZ(1);

    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcdZZ(abs(x - y), n);
    }

    if (d == n)
        return ZZ(1); 
    return d;
}

ZZ Pollard::pollardPMinus1() {
    ZZ a = ZZ(2);
    ZZ d;

    for (int j = 2; j < 500; j++) {
        a = PowerMod(a, j, n);  
        d = gcdZZ(a - 1, n);

        if (d > 1 && d < n)
            return d;
    }
    return ZZ(1);
}

