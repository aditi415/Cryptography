#include "el-gamal.hpp"

ElGamalDH::ElGamalDH() {
}

void ElGamalDH::generateParameters(long bits) {
    p = GenPrime_ZZ(bits); 
    g = RandomBnd(p - 2) + 2; 
    cout << "Generated Prime (p): " << p << endl;
    cout << "Generator (g): " << g << endl;
}


ZZ ElGamalDH::modExp(const ZZ& base, const ZZ& exp, const ZZ& mod) {
    return PowerMod(base, exp, mod);
}

void ElGamalDH::diffieHellman() {
    cout << "\n Diffie-Hellman Key Exchange" << endl;
    generateParameters();

    ZZ a = RandomBnd(p - 2) + 1; 
    ZZ b = RandomBnd(p - 2) + 1; 

    ZZ A = modExp(g, a, p); 
    ZZ B = modExp(g, b, p); 

    ZZ sharedA = modExp(B, a, p); 
    ZZ sharedB = modExp(A, b, p); 
    
    cout << "Alice's public key (A): " << A << endl;
    cout << "Bob's public key (B): " << B << endl;
    cout << "Shared secret key (Alice): " << sharedA << endl;
    cout << "Shared secret key (Bob): " << sharedB << endl;
}

void ElGamalDH::ElGamal() {
    cout << "\nElGamal Encryption & Decryption " << endl;
    generateParameters();

    ZZ privateKey = RandomBnd(p - 2) + 1; 
    ZZ publicKey = modExp(g, privateKey, p);

    cout << "Private key: " << privateKey << endl;
    cout << "Public key: " << publicKey << endl;

    ZZ msg;
    cout << "Enter message (as number < p): ";
    cin >> msg;

    ZZ k = RandomBnd(p - 2) + 1; 
    ZZ c1 = modExp(g, k, p);
    ZZ c2 = (msg * modExp(publicKey, k, p)) % p;

    cout << "Ciphertext: (" << c1 << ", " << c2 << ")" << endl;

    ZZ s = modExp(c1, privateKey, p);
    ZZ s_inv = InvMod(s, p);
    ZZ decrypted = (c2 * s_inv) % p;

    cout << "Decrypted message: " << decrypted << endl;
}

