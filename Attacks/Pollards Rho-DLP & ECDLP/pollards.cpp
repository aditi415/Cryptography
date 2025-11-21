#include "pollards.hpp"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
using namespace NTL;

static ZZ to_ZZ(long long x) { return ZZ(x); }

Pollard::Point Pollard::add(Point P, Point Q, long long a, long long p) {

    ZZ_p::init(to_ZZ(p));

    ZZ_p Px = to_ZZ(P.x);
    ZZ_p Py = to_ZZ(P.y);
    ZZ_p Qx = to_ZZ(Q.x);
    ZZ_p Qy = to_ZZ(Q.y);

    ZZ_p slope = (Qy - Py) * inv(Qx - Px);

    ZZ_p xr = slope * slope - Px - Qx;
    ZZ_p yr = slope * (Px - xr) - Py;

    Point R;
    R.x = conv<long long>(xr);
    R.y = conv<long long>(yr);
    return R;
}

Pollard::Point Pollard::dbl(Point P, long long a, long long p) {

    ZZ_p::init(to_ZZ(p));

    ZZ_p Px = to_ZZ(P.x);
    ZZ_p Py = to_ZZ(P.y);

    ZZ_p slope = (to_ZZ(3) * Px * Px + to_ZZ(a)) * inv(to_ZZ(2) * Py);

    ZZ_p xr = slope * slope - Px - Px;
    ZZ_p yr = slope * (Px - xr) - Py;

    Point R;
    R.x = conv<long long>(xr);
    R.y = conv<long long>(yr);
    return R;
}
long long Pollard::DLP(long long p, long long g, long long h) {

    ZZ_p::init(to_ZZ(p));

    ZZ_p G = to_ZZ(g);
    ZZ_p H = to_ZZ(h);

    ZZ_p x = to_ZZ(1);
    long long a1 = 1, b1 = 1;

    ZZ_p X = to_ZZ(1);
    long long A = 1, B = 1;

    while (true) {
        if (conv<long long>(x) % 3 == 0) {
            x = x * G;
            a1++;
        }
        else if (conv<long long>(x) % 3 == 1) {
            x = x * H;
            b1++;
        }
        else {
            x = x * x;
            a1 *= 2;
            b1 *= 2;
        }
        for (int i = 0; i < 2; i++) {
            if (conv<long long>(X) % 3 == 0) {
                X = X * G; A++;
            }
            else if (conv<long long>(X) % 3 == 1) {
                X = X * H; B++;
            }
            else {
                X = X * X; A *= 2; B *= 2;
            }
        }

        if (x == X) {
            long long num = (a1 - A + (p - 1)) % (p - 1);
            long long den = (B - b1 + (p - 1)) % (p - 1);

            ZZ invDen = InvMod(to_ZZ(den), to_ZZ(p - 1));
            ZZ res = to_ZZ(num) * invDen % to_ZZ(p - 1);
            return conv<long long>(res);
        }
    }
}

long long Pollard::ECDLP(long long p, long long a, long long b,
                         long long Px, long long Py,
                         long long Qx, long long Qy) {

    Point P = {Px, Py};
    Point Q = {Qx, Qy};

    Point X = P;    long long a1 = 1, b1 = 0;
    Point Y = P;    long long A = 1, B = 0;

    while (true) {
        if (X.x % 3 == 0) { X = add(X, P, a, p); a1++; }
        else if (X.x % 3 == 1) { X = add(X, Q, a, p); b1++; }
        else { X = dbl(X, a, p); a1 *= 2; b1 *= 2; }

        for (int i = 0; i < 2; i++) {
            if (Y.x % 3 == 0) { Y = add(Y, P, a, p); A++; }
            else if (Y.x % 3 == 1) { Y = add(Y, Q, a, p); B++; }
            else { Y = dbl(Y, a, p); A *= 2; B *= 2; }
        }

        if (X.x == Y.x && X.y == Y.y) {
            long long num = (a1 - A + p) % p;
            long long den = (B - b1 + p) % p;

            ZZ invDen = InvMod(to_ZZ(den), to_ZZ(p));
            ZZ k = to_ZZ(num) * invDen % to_ZZ(p);
            return conv<long long>(k);
        }
    }
}

