#ifndef ElGamal_DH_HPP
#define ElGamal_DH_HPP

#include <NTL/ZZ.h>
#include <iostream>
using namespace NTL;
using namespace std;

class ElGamalDH {
private:
    ZZ p, g; 

public:
    void inputParameters();
    void diffieHellman();
    void elGamal();

private:
    ZZ modExp(const ZZ& base, const ZZ& exp, const ZZ& mod);
};

#endif
