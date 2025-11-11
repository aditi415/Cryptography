#include "ecdlp.hpp"

EllipticCurve::EllipticCurve(ZZ_p _a, ZZ_p _b) {
    a = _a;
    b = _b;
}

Point EllipticCurve::add(Point P, Point Q) {
    if (P.inf) 
      return Q;
    if (Q.inf) 
      return P;
    if (P.x == Q.x && P.y == -Q.y) 
      return Point(); 

    ZZ_p lambda;
    if (P.x != Q.x)
        lambda = (Q.y - P.y) / (Q.x - P.x);
    else
        lambda = (ZZ_p(3)*P.x*P.x + a) / (ZZ_p(2)*P.y);

    ZZ_p xr = lambda*lambda - P.x - Q.x;
    ZZ_p yr = lambda*(P.x - xr) - P.y;
    return Point(xr, yr);
}

Point EllipticCurve::mul(Point P, long long k) {
    Point R;
    Point Q = P;
    while (k > 0) {
        if (k & 1) R = add(R, Q);
        Q = add(Q, Q);
        k >>= 1;
    }
    return R;
}

