#include <iostream>
#include "ecdlp.hpp"
using namespace std;
using namespace NTL;

int main() {
    ZZ p = conv<ZZ>(11);
    ZZ_p::init(p);   
    ZZ_p a = conv<ZZ_p>(1), b = conv<ZZ_p>(6);
    EllipticCurve E(a, b);

    Point G(conv<ZZ_p>(2), conv<ZZ_p>(4));

    cout << "Curve: y^2 = x^3 + x + 6 (mod 11)\n";
    cout << "Base Point G = (" << rep(G.x) << "," << rep(G.y) << ")\n\n";

    long long private_key = 7;
    Point public_key = E.mul(G, private_key);

    cout << "Private key = " << private_key << endl;
    cout << "Public key  = (" << rep(public_key.x) << "," << rep(public_key.y) << ")\n\n";

    long long k = 3; 
    Point C1 = E.mul(G, k);
    Point shared = E.mul(public_key, k);

    ZZ_p M = conv<ZZ_p>(9); 
    ZZ_p C2 = M + shared.x; 

    cout << "Encryption:\n";
    cout << "  Random k = " << k << endl;
    cout << "  C1 = (" << rep(C1.x) << "," << rep(C1.y) << ")\n";
    cout << "  C2 = " << rep(C2) << endl << endl;

    Point shared_dec = E.mul(C1, private_key);
    ZZ_p M_decrypted = C2 - shared_dec.x;

    cout << "Decryption:\n";
    cout << "  Shared (x) = " << rep(shared_dec.x) << endl;
    cout << "  Decrypted M = " << rep(M_decrypted) << endl << endl;

    ZZ_p msg = conv<ZZ_p>(5); 
    long long rand_k = 4;     
    Point R = E.mul(G, rand_k);
    ZZ_p r = R.x;

    ZZ_p s = (inv(ZZ_p(rand_k)) * (msg + r * conv<ZZ_p>(private_key)));

    cout << "Digital Signature:\n";
    cout << "  r = " << rep(r) << ", s = " << rep(s) << endl << endl;

    ZZ_p w = inv(s);
    ZZ_p u1 = msg * w;
    ZZ_p u2 = r * w;
    Point P1 = E.mul(G, conv<long>(rep(u1)));
    Point P2 = E.mul(public_key, conv<long>(rep(u2)));
    Point X = E.add(P1, P2);

    cout << "Verification:\n";
    cout << "  Computed r' = " << rep(X.x) << endl;
    if (X.x == r) cout << "Signature Verified!\n";
    else cout << "Signature Failed!\n";
}

