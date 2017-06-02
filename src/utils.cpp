#include "utils.hpp"

using crypto::Number;
using crypto::TotientAlgorithm;
using crypto::FactorizationAlgorithm;

Number crypto::gcd(NumberView a, NumberView b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

template<typename F>
Number crypto::detail::pow(Number base, Number exponent, const F& mult) {
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

Number crypto::pow(Number base, Number exponent) {
    return detail::pow(base, exponent, [](NumberView a, NumberView b) {
        return a * b;
    });
}

Number crypto::pow(Number base, Number exponent, Number modulus) {
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

template<typename F>
std::vector<Number> crypto::detail::primitiveRoots(NumberView n, NumberView alpha, const F& threshold) {
    std::vector<Number> result;
    auto totient = phi<TotientAlgorithm::prime>(n);
    Number i = 2;
    while (i < n) {
        if (gcd(totient, i) == 1) {
            result.push_back(::crypto::pow(alpha, i, n));
        }
        ++i;
        if (threshold(result.size())) {
            break;
        }
    }
    return result;
}

std::vector<Number> crypto::primitiveRoots(NumberView p, NumberView alpha) {
    return detail::primitiveRoots(p, alpha, [](std::size_t size) {
        return false;
    });
}

std::vector<Number> crypto::primitiveRoots(NumberView p, NumberView alpha, NumberView limit) {
    return detail::primitiveRoots(p, alpha, [&limit](std::size_t size) {
        return size >= limit;
    });
}

template<>
std::vector<Number> crypto::factorize<FactorizationAlgorithm::naive>(NumberView n) {
    // TODO
    return {};
}

// Euler's totient function
template<>
Number crypto::phi<TotientAlgorithm::naive>(NumberView n) {
    Number viable = 0;
    for (Number i = 1; i < n; ++i) {
        if (gcd(n, i) == 1) {
            ++viable;
        }
    }
    return viable;
}

Number crypto::phi(Number n, const std::vector<Number>& factors) {
    for (const auto& factor : factors) {
        n /= factor;
        n *= (factor - 1);
    }
    return n;
}
