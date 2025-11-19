#ifndef POLLARD_RHO_RADDING_HPP
#define POLLARD_RHO_RADDING_HPP

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <vector>

using namespace NTL;
using namespace std;

struct DLPState {
    ZZ x;   
    ZZ a;   
    ZZ b;   
    DLPState() : x(ZZ(0)), a(ZZ(0)), b(ZZ(0)) {}
};

struct DLPTableEntry {
    ZZ mul;  
    ZZ alpha; 
    ZZ beta;  
};

ZZ inv_mod_safe(const ZZ &a, const ZZ &m);

ZZ pollard_rho_radding_dlp(const ZZ &p, const ZZ &g, const ZZ &h, long r = 16, long max_iters = 0);

#endif 

