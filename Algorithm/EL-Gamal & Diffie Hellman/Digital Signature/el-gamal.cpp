#include "el-gamal.hpp"

CryptoSystem::CryptoSystem(long bits) {
    p = GenPrime_ZZ(bits);  
    g = conv<ZZ>(2);         
    ZZ_p::init(p);
    cout << "\nGenerated Prime (p): " << p << "\nGenerator (g): " << g << endl;
}

void CryptoSystem::diffieHellman() {
    cout << "\n Diffie-Hellman Key Exchange (ZZ_p) " << endl;

    ZZ a = RandomBnd(p-2) + 1;
    ZZ b = RandomBnd(p-2) + 1;

    ZZ_p g_p = to_ZZ_p(g);
    ZZ_p A = power(g_p, a);
    ZZ_p B = power(g_p, b);

    cout << "Alice's Public Key (A): " << A << endl;
    cout << "Bob's Public Key (B): " << B << endl;

    ZZ_p sharedA = power(B, a);
    ZZ_p sharedB = power(A, b);

    cout << "Shared Key (Alice): " << sharedA << endl;
    cout << "Shared Key (Bob): " << sharedB << endl;
}

void CryptoSystem::elgamalEncryptDecrypt() {
    cout << "\n ElGamal Encryption & Decryption " << endl;

    ZZ_p g_p = to_ZZ_p(g);

    ZZ x = RandomBnd(p-2) + 1;
    ZZ_p y = power(g_p, x);

    cout << "Private key (x): " << x << endl;
    cout << "Public key (y): " << y << endl;

    long m;
    cout << "Enter message (integer < p): ";
    cin >> m;
    ZZ_p M = conv<ZZ_p>(m);

    ZZ k = RandomBnd(p-2) + 1;
    ZZ_p c1 = power(g_p, k);      
    ZZ_p c2 = M * power(y, k);       

    cout << "Ciphertext: (c1=" << c1 << ", c2=" << c2 << ")" << endl;

    ZZ_p M_dec = c2 / power(c1, x);
    cout << "Decrypted message: " << M_dec << endl;
}

void CryptoSystem::elgamalSignature() {
    cout << "\n ElGamal Digital Signature" << endl;

    ZZ_p g_p = to_ZZ_p(g);

    ZZ x = RandomBnd(p-2) + 1;
    ZZ_p y = power(g_p, x);

    cout << "Private key (x): " << x << endl;
    cout << "Public key (y): " << y << endl;

    long m;
    cout << "Enter message to sign (integer < p): ";
    cin >> m;
    ZZ M = conv<ZZ>(m);

    ZZ k;
    do {
        k = RandomBnd(p-2) + 1;
    } while (GCD(k, p-1) != 1);

    ZZ_p::init(p);
    ZZ_p gk = power(to_ZZ_p(g), k);
    ZZ r = rep(gk); 
    ZZ kinv = InvMod(k, p-1);

    ZZ s = (kinv * (M - x * r)) % (p - 1);
    if (s < 0) s += (p - 1);

    cout << "Signature: (r=" << r << ", s=" << s << ")" << endl;
    
    ZZ_p left = power(to_ZZ_p(g), conv<ZZ>(M)); 
    ZZ_p right = (power(y, r) * power(to_ZZ_p(r), s)); 

    cout << "Verification: ";
    if (left == right)
        cout << "Valid Signature" << endl;
    else
        cout << "Invalid Signature" << endl;
}

