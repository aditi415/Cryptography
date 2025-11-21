#ifndef POLLARD_HPP
#define POLLARD_HPP

#include <NTL/ZZ.h>
using namespace NTL;

class Pollard {
public:
    Pollard(const ZZ& n);

    ZZ pollardRho();
    ZZ pollardPMinus1();

private:
    ZZ n;
    ZZ f(const ZZ &x);     
    ZZ gcdZZ(const ZZ &a, const ZZ &b);
};

#endif

