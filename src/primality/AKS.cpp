#include <cmath>
#include <iostream>
#include "primality/AKS.hpp"
#include "utils.hpp"

bool crypto::AKS::test(NumberView n) {
    if (isPerfectPower(n)) {
        return false;
    }

    auto r = findR(n);
    std::cout << "[AKS] r = " << r << std::endl;
    {
        auto boundary = std::min(r, n - 1);

        for (Number a = 2; a <= boundary; a++) {
            if (n % a == 0) {
                return false;
            }
        }

        if (n <= r) {
            return true;
        }
    }

    auto boundary = floor(std::log2(n) * std::sqrt(phi(r)));
    std::cout << "[AKS] boundary = " << boundary << std::endl;
    for (Number a = 1; a <= boundary; a++) {
        if (!testANR(a, n, r)) {
            return false;
        }
    }

    return true;
}

// source: https://cstheory.stackexchange.com/questions/2077/how-to-check-if-a-number-is-a-perfect-power-in-polynomial-time
bool crypto::AKS::isPerfectPower(NumberView n) {
    auto lg = std::log2(n);
    if (lg - floor(lg) < 1e-6) {
        return true; // n = 2^k
    }

    for (Number i = 2; i <= lg; i++) {
        Number begin = 1;
        Number end = begin << Number(lg / i + 1);
        while (begin < end - 1) {
            auto middle = (begin + end) >> 1;
            auto power = pow(middle, i);
            if (power > n) {
                end = middle;
            } else if (power < n) {
                begin = middle;
            } else {
                return true; // n = middle^i
            }
        }
    }
    return false;
}

crypto::Number crypto::AKS::findR(NumberView n) {
    auto lg = std::log2(n);
    auto maxk = floor(lg * lg);
    // auto maxr = std::max(3, ceil(std::pow(lg, 5)));
    Number r = 2;
    bool loop = true;
    while (loop) {
        loop = false;
        for (Number k = 1; !loop && k <= maxk; k++) {
            auto mod = pow(n, k, r);
            loop = (mod == 0 || mod == 1);
        }
        r++;
    }
    return r - 1;
}

crypto::Number crypto::AKS::degree(const Polynomial& poly, NumberView r) {
    Number deg = r - 1;
    while (deg > 0 && !poly[deg]) {
        deg--;
    }
    return deg;
}

void crypto::AKS::polyMultMod(Polynomial& px, const Polynomial& py, const Polynomial& temp, NumberView r, NumberView modulus) {
    // Number degPx = degree(px, r);
    // Number degPy = degree(py, r);
    // Number j = 
}

crypto::Polynomial crypto::AKS::polyPowMod(const Polynomial& poly, Number exponent, NumberView r, NumberView modulus) {
    Polynomial result(r, 0);
    result[0] = 1;

    Polynomial temp;
    temp.reserve(r);

    while (exponent > 0) {
        if (exponent & 1) {
            polyMultMod(result, poly, temp, r, modulus);
        }
        // polySqrMod(poly, temp, r, modulus);
        exponent >>= 1;
    }
    return result;
}

bool crypto::AKS::testANR(Number a, NumberView n, NumberView r) {
    // a %= r;
    // Polynomial polynomial(r, 0);
    // polynomial[0] = a;
    // polynomial[1] = 1;

    // auto powmod = polyPowMod(polynomial, n, r, n);
    // powmod[n % r] = addMod(res[n % r], n - 1, n);
    // powmod[0] = addMod(res[0], n - a, n);

    // for (Number i = 0; i < r; i++) {
    //     if (powmod[i] != 0) {
    //         return false;
    //     }
    // }
    return true;
}
