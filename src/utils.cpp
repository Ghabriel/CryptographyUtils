#include "utils.hpp"

using crypto::Number;
using crypto::TotientAlgorithm;

Number crypto::operations::gcd(NumberView a, NumberView b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

template<typename F>
Number crypto::operations::detail::pow(Number base, Number exponent, const F& mult) {
    Number result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = mult(result, base);
        }
        base = mult(base, base);
        exponent >>= 1;
    }
    return result;
}

// Fast exponentiation. Returns base^exponent.
Number crypto::operations::pow(Number base, Number exponent) {
    return detail::pow(base, exponent, [](NumberView a, NumberView b) {
        return a * b;
    });
}

// Returns base^exponent mod modulus.
Number crypto::operations::pow(Number base, Number exponent, Number modulus) {
    // Number result = 1;
    // while (exponent > 0) {
    //     if (exponent & 1) {
    //         result = (result * base) % modulus;
    //     }
    //     base = (base * base) % modulus;
    //     exponent >>= 1;
    // }
    // return result;
    return detail::pow(base, exponent, [&modulus](NumberView a, NumberView b) {
        return (a * b) % modulus;
    });
}

// Euler's totient function
template<>
Number crypto::operations::phi<TotientAlgorithm::naive>(NumberView n) {
    Number viable = 0;
    for (Number i = 1; i < n; i++) {
        if (gcd(n, i) == 1) {
            viable++;
        }
    }
    return viable;
}

Number crypto::operations::phi(Number n, const std::vector<Number>& factors) {
    for (const auto& factor : factors) {
        n /= factor;
        n *= (factor - 1);
    }
    return n;
}
