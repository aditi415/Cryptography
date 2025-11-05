#include "el-gamal.hpp"

ELGDH::ELGDH() {
    p = RandomPrime_ZZ(40);
    g = conv<ZZ>(2);        
    ZZ_p::init(p);          
}

void ELGDH::diffieHellman() {
    cout << "\nDiffie-Hellman Key Exchange\n";
    ZZ a = RandomBnd(p - 2) + 1;
    ZZ b = RandomBnd(p - 2) + 1;

    ZZ_p A = power(to_ZZ_p(g), a);
    ZZ_p B = power(to_ZZ_p(g), b);

    ZZ_p sharedA = power(B, a);
    ZZ_p sharedB = power(A, b);

    cout << "Prime (p): " << p << "\nGenerator (g): " << g << endl;
    cout << "Alice Public (A): " << A << "\nBob Public (B): " << B << endl;
    cout << "Shared Key (Alice): " << sharedA << "\nShared Key (Bob): " << sharedB << endl;
}

void ELGDH::elgamalEncryption() {
    cout << "\n ElGamal Encryption\n";
    ZZ x = RandomBnd(p - 2) + 1; 
    ZZ_p y = power(to_ZZ_p(g), x); 

    ZZ msgInt;
    cout << "Enter message (integer < p): ";
    cin >> msgInt;

    ZZ_p M = to_ZZ_p(msgInt);
    ZZ k = RandomBnd(p - 2) + 1;

    ZZ_p c1 = power(to_ZZ_p(g), k);
    ZZ_p c2 = M * power(y, k);

    cout << "Ciphertext: (c1=" << c1 << ", c2=" << c2 << ")\n";

    ZZ_p M_dec = c2 / power(c1, x);
    cout << "Decrypted message: " << M_dec << endl;
}

pair<ZZ_p, ZZ_p> ELGDH::generateSignature(const ZZ_p& m, const ZZ_p& x, const ZZ_p& g) {
    ZZ k;
    do {
        k = RandomBnd(p - 2) + 1;
    } while (GCD(k, p - 1) != 1);

    ZZ_p r = power(g, k);
    ZZ kinv = InvMod(k, p - 1);
    ZZ_p s = to_ZZ_p((kinv * (rep(m) - rep(x) * rep(r))) % (p - 1));

    return {r, s};
}

bool ELGDH::verifySignature(const ZZ_p& m, const ZZ_p& r, const ZZ_p& s,const ZZ_p& y, const ZZ_p& g) {
    ZZ_p left = power(y, rep(r)) * power(r, rep(s));
    ZZ_p right = power(g, rep(m));
    return (left == right);
}

void ELGDH::elgamalSignature() {
    cout << "\n ElGamal Digital Signature\n";
    ZZ x = RandomBnd(p - 2) + 1;
    ZZ_p y = power(to_ZZ_p(g), x);

    cout << "Public Key (y): " << y << "\nPrivate Key (x): " << x << endl;

    ZZ msgInt;
    cout << "Enter message to sign (integer < p): ";
    cin >> msgInt;
    ZZ_p M = to_ZZ_p(msgInt);

    auto [r, s] = generateSignature(M, to_ZZ_p(x), to_ZZ_p(g));
    cout << "Signature: (r=" << r << ", s=" << s << ")\n";

    bool valid = verifySignature(M, r, s, y, to_ZZ_p(g));
    cout << "Verification: " << (valid ? "Valid " : "Invalid ") << endl;
}

