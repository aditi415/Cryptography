#include <iostream>
#include <NTL/ZZ.h>
#include "rsa.hpp"

using namespace std;
using namespace NTL;

int main() {
    RSA rsa;
    rsa.generateKeys(256);

    cout << "Public Key (e, n): " << rsa.e << ", " << rsa.n << endl;
    cout << "Private Key (d, n): " << rsa.d << ", " << rsa.n << endl;

    long x;
    cout << "Enter a number (< n): ";
    cin >> x;

    ZZ msg = ZZ(x);

    ZZ encrypted = rsa.encrypt(msg);
    cout << "Encrypted: " << encrypted << endl;

    ZZ decrypted = rsa.decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;

    ZZ signature = rsa.sign(msg);
    cout << "Signature: " << signature << endl;

    if (rsa.verify(msg, signature))
        cout << "Signature Verified!" << endl;
    else
        cout << "Signature Failed!" << endl;

    return 0;
}

