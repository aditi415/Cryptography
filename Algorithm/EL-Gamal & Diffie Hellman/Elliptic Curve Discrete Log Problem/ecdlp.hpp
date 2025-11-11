
//#pragma once
#include <NTL/ZZ_p.h>
using namespace NTL;

struct Point {
    ZZ_p x, y;
    bool inf;
    Point() : x(ZZ_p::zero()), y(ZZ_p::zero()), inf(true) {}
    Point(ZZ_p _x, ZZ_p _y) : x(_x), y(_y), inf(false) {}
};

class EllipticCurve {
public:
    ZZ_p a, b;
    EllipticCurve(ZZ_p _a, ZZ_p _b);
    Point add(Point P, Point Q);
    Point mul(Point P, long long k);
};

