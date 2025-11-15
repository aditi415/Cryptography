#include "rsa.hpp"
#include <NTL/ZZ.h>
#include <iostream>

using namespace std;
using namespace NTL;

RSA::RSA() {
    SetSeed(to_ZZ(time(NULL))); 
}

ZZ RSA::generatePrime(long bits) {
    ZZ prime;
    GenPrime(prime, bits);
    return prime;
}

void RSA::generateKeys(long bits) {
    p = generatePrime(bits);
    q = generatePrime(bits);

    n = p * q;
    
    phi = (p - 1) * (q - 1);

    e = ZZ(65537);  
    d = InvMod(e, phi);
}

ZZ RSA::encrypt(const ZZ& msg) {
    return PowerMod(msg, e, n);
}

ZZ RSA::decrypt(const ZZ& cipher) {
    return PowerMod(cipher, d, n);
}

ZZ RSA::sign(const ZZ& msg) {
    return PowerMod(msg, d, n);
}

bool RSA::verify(const ZZ& msg, const ZZ& signature) {
    ZZ check = PowerMod(signature, e, n);
    return check == msg;
}

