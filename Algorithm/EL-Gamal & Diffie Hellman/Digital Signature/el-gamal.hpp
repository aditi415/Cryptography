#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <NTL/ZZ_p.h>
#include <NTL/ZZ.h>
#include <iostream>
using namespace std;
using namespace NTL;

class CryptoSystem {
private:
    ZZ p;      
    ZZ g;  

public:
    CryptoSystem(long bits = 32);   
    void diffieHellman();
    void elgamalEncryptDecrypt();
    void elgamalSignature();
};

#endif

