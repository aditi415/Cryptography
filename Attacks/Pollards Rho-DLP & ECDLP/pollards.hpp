#ifndef POLLARDS_HPP
#define POLLARDS_HPP

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

using namespace NTL;

class Pollard {
public:
    struct Point {
        long long x;
        long long y;
    };
    long long DLP(long long p, long long g, long long h);
    long long ECDLP(long long p, long long a, long long b,long long Px, long long Py,long long Qx, long long Qy);

private:
    Point add(Point P, Point Q, long long a, long long p);
    Point dbl(Point P, long long a, long long p);
};

#endif

