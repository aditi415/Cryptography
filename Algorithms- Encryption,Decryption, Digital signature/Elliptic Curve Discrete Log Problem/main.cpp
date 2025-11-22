#include "ecdlp.hpp"
using namespace std;
using namespace NTL;

int main() {
    ZZ p = conv<ZZ>(11);
    ZZ_p::init(p);
    EllipticCurve curve(p, conv<ZZ_p>(1), conv<ZZ_p>(6));
    curve.printParams();

    // Base point (example)
    Point G(conv<ZZ_p>(2), conv<ZZ_p>(7));

    // Private & Public keys
    long privateKey = 3;
    Point publicKey = curve.multiply(G, privateKey);
    cout << "\nPrivate Key: " << privateKey << endl;
    cout << "Public Key: (" << publicKey.x << ", " << publicKey.y << ")" << endl;

    // Message point
    Point M(conv<ZZ_p>(5), conv<ZZ_p>(9));
    cout << "\nMessage Point: (" << M.x << ", " << M.y << ")" << endl;

    // Encryption
    long k = 2;
    auto cipher = curve.encrypt(M, publicKey, G, k);
    cout << "\nEncrypted Points:";
    cout << "\nC1: (" << cipher.first.x << ", " << cipher.first.y << ")";
    cout << "\nC2: (" << cipher.second.x << ", " << cipher.second.y << ")" << endl;

    // Decryption
    Point D = curve.decrypt(cipher, privateKey);
    cout << "\nDecrypted Message: (" << D.x << ", " << D.y << ")" << endl;

    // Digital Signature
    ZZ_p msg = conv<ZZ_p>(5); // example message
    auto sig = curve.sign(msg, privateKey, G, k);
    cout << "\nSignature: (r=" << sig.first << ", s=" << sig.second << ")" << endl;

    bool valid = curve.verify(msg, sig, publicKey, G);
    cout << "Signature Valid? " << (valid ? "Yes" : "No") << endl;

    return 0;
}
