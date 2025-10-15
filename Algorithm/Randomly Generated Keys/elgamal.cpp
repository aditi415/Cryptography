#include "elgamal.hpp"

void ElGamalDH::keygen(long bits) {
    GenPrime(p, bits);
    g = RandomBnd(p - 2) + 2; 
    x = RandomBnd(p - 2) + 1; 
    y = PowerMod(g, x, p);
}

void ElGamalDH::encrypt(const ZZ &m, ZZ &c1, ZZ &c2) {
    ZZ k = RandomBnd(p - 2) + 1;      
    c1 = PowerMod(g, k, p);
    c2 = (m * PowerMod(y, k, p)) % p;
}

ZZ ElGamalDH::decrypt(const ZZ &c1, const ZZ &c2) {
    ZZ s = PowerMod(c1, x, p);
    ZZ inv_s = InvMod(s, p);
    return (c2 * inv_s) % p;
}

void ElGamalDH::params(long bits) {
    GenPrime(p, bits);
    g = RandomBnd(p - 2) + 2; 
}

void ElGamalDH::generate_keys() {
    priv = RandomBnd(p - 2) + 1;
    pub = PowerMod(g, priv, p);
}

ZZ ElGamalDH::compute_shared(const ZZ &other_pub) {
    return PowerMod(other_pub, priv, p);
}

