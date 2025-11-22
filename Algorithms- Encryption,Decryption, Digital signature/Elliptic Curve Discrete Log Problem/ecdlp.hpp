#ifndef ELLIPTIC_HPP
#define ELLIPTIC_HPP

#include <NTL/ZZ_p.h>
#include <iostream>
using namespace std;
using namespace NTL;

struct Point {
    ZZ_p x;
    ZZ_p y;
    bool infinity;

    Point() : infinity(true) {}
    Point(ZZ_p _x, ZZ_p _y) : x(_x), y(_y), infinity(false) {}
};

class EllipticCurve {
private:
    ZZ_p a, b;
    ZZ p;
public:
    EllipticCurve(ZZ _p, ZZ_p _a, ZZ_p _b);
    void printParams();

    Point add(Point P, Point Q);
    Point multiply(Point P, long k);

    Point encrypt(Point message, Point publicKey, Point basePoint, long k);
    Point decrypt(Point cipher, long privateKey, Point basePoint, long k);

    pair<ZZ, ZZ> sign(ZZ message, long privateKey, Point basePoint, long k);
    bool verify(ZZ message, pair<ZZ, ZZ> signature, Point publicKey, Point basePoint);
};

#endif
