#include <stack>
#include "primality/LucasTest.hpp"

bool crypto::LucasTest::test(NumberView n, NumberView d, NumberView p, NumberView q) const {
    Number u = 0;
    Number v = 2;
    Number exponent = 1;
    Number i = 0;

    auto next = [&]() {
        auto prevU = u;
        u = p * u + v;
        if (u % 2 != 0) u += n;
        u = (u / 2) % n;

        v = d * prevU + p * v;
        if (v % 2 != 0) v += n;
        v = (v / 2) % n;

        exponent = (exponent * q) % n;
        ++i;
    };

    auto jump = [&]() {
        u = (u * v) % n;
        v = (v * v) - 2 * exponent;
        v %= n;
        exponent = (exponent * exponent) % n;
        i <<= 1;
    };

    std::stack<short> bits;
    auto goal = n + 1;
    while (goal > 0) {
        bits.push(goal & 1);
        goal >>= 1;
    }

    while (!bits.empty()) {
        jump();
        if (bits.top() == 1) {
            next();
        }
        bits.pop();
    }

    return u == 0 && (v - 2 * q) % n == 0;
}
