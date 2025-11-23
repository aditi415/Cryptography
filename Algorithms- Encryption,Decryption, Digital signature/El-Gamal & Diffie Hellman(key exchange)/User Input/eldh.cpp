#include "eldh.hpp"

ZZ ElGamalDH::modExp(const ZZ& base, const ZZ& exp, const ZZ& mod) {
    return PowerMod(base, exp, mod);
}

void ElGamalDH::inputParameters() {
    cout << "\nEnter prime number (p): ";
    cin >> p;
    cout << "Enter generator (g): ";
    cin >> g;
}

void ElGamalDH::diffieHellman() {
    cout << "\nDiffie-Hellman Key Exchange" << endl;
    inputParameters();

    ZZ a, b;
    cout << "Enter Alice's private key (a): ";
    cin >> a;
    cout << "Enter Bob's private key (b): ";
    cin >> b;

    ZZ A = modExp(g, a, p);
    ZZ B = modExp(g, b, p); 

    ZZ sharedA = modExp(B, a, p);
    ZZ sharedB = modExp(A, b, p);

    cout << "\nAlice's Public Key (A): " << A << endl;
    cout << "Bob's Public Key (B): " << B << endl;
    cout << "Shared Secret (Alice): " << sharedA << endl;
    cout << "Shared Secret (Bob): " << sharedB << endl;
}

void ElGamalDH::elGamal() {
    cout << "\nElGamal Encryption & Decryption" << endl;
    inputParameters();

    ZZ privateKey, message;
    cout << "Enter private key (x): ";
    cin >> privateKey;

    ZZ publicKey = modExp(g, privateKey, p);
    cout << "Public key (h = g^x mod p): " << publicKey << endl;

    cout << "Enter message m : ";
    cin >> message;

    ZZ y;
    cout << "Enter random key (y): ";
    cin >> y;

    ZZ c1 = modExp(g, y, p);
    ZZ c2 = (message * modExp(publicKey, y, p)) % p;

    cout << "\nCiphertext (c1, c2): (" << c1 << ", " << c2 << ")" << endl;

    ZZ s = modExp(c1, privateKey, p);
    ZZ s_inv = InvMod(s, p);
    ZZ decrypted = (c2 * s_inv) % p;

    cout << "Decrypted message: " << decrypted << endl;
}
