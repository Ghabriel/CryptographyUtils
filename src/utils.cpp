#include <cmath>
#include <random>
#include "debug.hpp"
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

Number crypto::primitiveRoot(NumberView p) {
    auto totient = phi<TotientAlgorithm::prime>(p);
    auto primeFactors = factorize<FactorizationAlgorithm::naive>(totient);
    for (Number m = 2; m < p; ++m) {
        bool success = true;
        for (auto& factor : primeFactors) {
            if (pow(m, totient / factor, p) == 1) {
                success = false;
                break;
            }
        }

        if (success) {
            return m;
        }
    }

    throw 1;
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
std::vector<Number> crypto::factorize<FactorizationAlgorithm::naive>(Number n) {
    std::vector<Number> result;
    Number upperBound = n >> 1;

    auto test = [&](NumberView i) {
        if (n % i == 0) {
            result.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
            upperBound = n >> 1;
        }
    };

    test(2);

    for (Number i = 3; i <= upperBound; i += 2) {
        test(i);
    }

    if (n > 1) {
        result.push_back(n);
    }

    return result;
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

Number crypto::random(NumberView min, NumberView max) {
    static std::random_device rng;
    auto value = (max - min) * rng();
    return min + value / std::random_device::max();
}
