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
    std::vector<Number> factorize(Number n);

    // Euler's totient function with a given list of prime factors
    Number phi(Number n, const std::vector<Number>& factors);

    // Euler's totient function
    template<TotientAlgorithm Algorithm = TotientAlgorithm::naive>
    Number phi(NumberView n);

    // Given a prime number p, returns a primitive root of p.
    // Throws an exception if no root is found (which should happen
    // only if p is not prime).
    Number primitiveRoot(NumberView p);

    // Given a prime number p and a primitive root alpha, returns other
    // primitive roots of p. If a limit is specified, stops searching after
    // 'limit' primitive roots are found, otherwise finds all of them.
    std::vector<Number> primitiveRoots(NumberView p, NumberView alpha);
    std::vector<Number> primitiveRoots(NumberView p, NumberView alpha, std::size_t limit);

    // Returns the Jacobi Symbol (a/n)
    short jacobiSymbol(Number a, Number n);

    // Checks if a given number is a perfect square, i.e
    // has an integer square root.
    bool isPerfectSquare(NumberView n);

    // Returns a cryptographycally secure random integer in the range [min, max)
    Number random(NumberView min, NumberView max);

    Number generatePrime();

    // ########## Function template specializations ##########

    template<>
    std::vector<Number> factorize<FactorizationAlgorithm::naive>(Number n);

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
