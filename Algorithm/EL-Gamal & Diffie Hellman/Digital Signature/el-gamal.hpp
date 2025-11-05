#ifndef EL_GAMAL_HPP
#define EL_GAMAL_HPP

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <iostream>
using namespace std;
using namespace NTL;

class ELGDH {
private:
    ZZ p; 
    ZZ g;

public:
    ELGDH(); 

    void diffieHellman();
    void elgamalEncryption();
    void elgamalSignature();

private:
    pair<ZZ_p, ZZ_p> generateSignature(const ZZ_p& m, const ZZ_p& x, const ZZ_p& g);
    bool verifySignature(const ZZ_p& m, const ZZ_p& r, const ZZ_p& s,const ZZ_p& y, const ZZ_p& g);
};

#endif

