#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <NTL/ZZ.h>
#include <iostream>
using namespace NTL;
using namespace std;

class ElGamalDH {
private:
    ZZ p, g;
    
public:
    ElGamalDH();
    void generateParameters(long bits = 64);
    void diffieHellman();
    void ElGamal();

private:
    ZZ modExp(const ZZ& base, const ZZ& exp, const ZZ& mod);
};

#endif

