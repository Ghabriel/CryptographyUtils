#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include "traits.hpp"

namespace crypto {
    enum class TotientAlgorithm {
        naive,
        factorize,
        prime
    };

    enum class FactorizationAlgorithm {
        naive
    };

    namespace detail {
        template<typename F>
        Number pow(Number base, Number exponent, const F&);

        template<typename F>
        std::vector<Number> primitiveRoots(NumberView, NumberView, const F&);
    }

    Number gcd(NumberView a, NumberView b);

    inline Number lcm(NumberView a, NumberView b) {
        return (a * b) / gcd(a, b);
    }

    // Fast exponentiation. Returns base^exponent.
    Number pow(Number base, Number exponent);

    // Returns base^exponent mod modulus.
    Number pow(Number base, Number exponent, Number modulus);

    // Integer factorization
    template<FactorizationAlgorithm Algorithm = FactorizationAlgorithm::naive>
    std::vector<Number> factorize(NumberView n);

    // Euler's totient function with a given list of prime factors
    Number phi(Number n, const std::vector<Number>& factors);

    // Euler's totient function
    template<TotientAlgorithm Algorithm = TotientAlgorithm::naive>
    Number phi(NumberView n);

    // template<bool = false>
    // Number primitiveRoot(NumberView n);

    // Given a prime number p and a primitive root alpha, returns other
    // primitive roots of p. If a limit is specified, stops searching after
    // 'limit' primitive roots are found, otherwise finds all of them.
    std::vector<Number> primitiveRoots(NumberView p, NumberView alpha);
    std::vector<Number> primitiveRoots(NumberView p, NumberView alpha, NumberView limit);

    // ########## Function template specializations ##########

    template<>
    std::vector<Number> factorize<FactorizationAlgorithm::naive>(NumberView n);

    template<>
    Number phi<TotientAlgorithm::naive>(NumberView n);

    template<>
    inline Number phi<TotientAlgorithm::factorize>(NumberView n) {
        return phi(n, factorize(n));
    }

    template<>
    inline Number phi<TotientAlgorithm::prime>(NumberView n) {
        return n - 1;
    }
}

#endif
