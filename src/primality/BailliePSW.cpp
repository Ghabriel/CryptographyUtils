#include "primality/BailliePSW.hpp"

bool crypto::BailliePSW::test(NumberView n) const {
    if (n < 3 || n % 2 == 0) {
        return (n == 2);
    }

    if (!MillerRabin().test(n, {2})) {
        return false;
    }

    if (isPerfectSquare(n)) {
        return false;
    }

    Number d = 5;
    while (jacobiSymbol(d, n) != -1) {
        d = (d >= 0 ? -(d + 2) : -(d - 2));
    }

    Number p = 1;
    Number q = (1 - d) / 4;
    return LucasTest().test(n, d, p, q);
}
