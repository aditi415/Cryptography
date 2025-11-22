#ifndef RSA_HPP
#define RSA_HPP

#include <NTL/ZZ.h>
using namespace NTL;

class RSA {
public:
    ZZ p, q, n, phi;
    ZZ e, d;

    RSA();

    void generateKeys(long bits = 256);

    ZZ encrypt(const ZZ& msg);
    ZZ decrypt(const ZZ& cipher);

    ZZ sign(const ZZ& msg);
    bool verify(const ZZ& msg, const ZZ& signature);

private:
    ZZ generatePrime(long bits);
};

#endif

