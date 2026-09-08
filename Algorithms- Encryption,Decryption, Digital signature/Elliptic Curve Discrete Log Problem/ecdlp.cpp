#include "ecdlp.hpp"

EllipticCurve::EllipticCurve(ZZ _p, ZZ_p _a, ZZ_p _b) {
    p = _p;
    ZZ_p::init(p);
    a = _a;
    b = _b;
}

void EllipticCurve::printParams() {
    cout << "Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")" << endl;
}

Point EllipticCurve::add(Point P, Point Q) {
    if (P.infinity) return Q;
    if (Q.infinity) return P;

    ZZ_p lambda;
    if (P.x == Q.x && P.y == -Q.y) return Point(); // infinity

    if (P.x != Q.x)
        lambda = (Q.y - P.y) / (Q.x - P.x);
    else
        lambda = (3 * P.x * P.x + a) / (2 * P.y);

    ZZ_p x3 = lambda * lambda - P.x - Q.x;
    ZZ_p y3 = lambda * (P.x - x3) - P.y;
    return Point(x3, y3);
}

Point EllipticCurve::multiply(Point P, long k) {
    Point R; // infinity
    Point Q = P;
    while (k > 0) {
        if (k & 1) R = add(R, Q);
        Q = add(Q, Q);
        k >>= 1;
    }
    return R;
}

// ---------------- Encryption / Decryption ----------------

pair<Point, Point> EllipticCurve::encrypt(Point M, Point publicKey, Point basePoint, long k) {
    // Cipher = (kG, M + k*PublicKey)
    Point C1 = multiply(basePoint, k);
    Point C2 = add(M, multiply(publicKey, k));
    return make_pair(C1, C2);
}

Point EllipticCurve::decrypt(pair<Point, Point> cipher, long privateKey) {
    // M = C2 - d*C1
    Point dC1 = multiply(cipher.first, privateKey);
    Point neg = Point(dC1.x, -dC1.y);
    return add(cipher.second, neg);
}

// ---------------- Digital Signature ----------------

pair<ZZ_p, ZZ_p> EllipticCurve::sign(ZZ_p message, long privateKey, Point basePoint, long k) {
    Point R = multiply(basePoint, k);
    ZZ_p r = R.x;
    ZZ_p k_inv = inv(conv<ZZ_p>(k));
    ZZ_p s = k_inv * (message + r * conv<ZZ_p>(privateKey));
    return make_pair(r, s);
}

bool EllipticCurve::verify(ZZ_p message, pair<ZZ_p, ZZ_p> signature, Point publicKey, Point basePoint) {
    ZZ_p r = signature.first;
    ZZ_p s = signature.second;
    ZZ_p w = inv(s);
    ZZ_p u1 = message * w;
    ZZ_p u2 = r * w;

    Point P1 = multiply(basePoint, to_long(rep(u1)));
    Point P2 = multiply(publicKey, to_long(rep(u2)));
    Point X = add(P1, P2);
    return (X.x == r);
}
