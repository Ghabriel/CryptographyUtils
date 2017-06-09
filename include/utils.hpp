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

    // Returns a cryptographycally secure random integer in the range [min, max)
    template<bool = std::is_integral<Number>::value>
    Number random(NumberView min, NumberView max);

    Number gcd(Number a, Number b);

    // Returns a tuple {x, y, z} such that ax + by = z and z = gcd(a, b)
    std::tuple<Number, Number, Number> xgcd(Number a, Number b);

    inline Number lcm(NumberView a, NumberView b) {
        // return (a * b) / gcd(a, b);
        return a * (b / gcd(a, b));
    }

    Number multInverse(NumberView n, NumberView modulus);

    // Fast exponentiation. Returns base^exponent.
    Number pow(Number base, Number exponent);

    // Returns base^exponent mod modulus.
    Number pow(Number base, Number exponent, Number modulus);

    // Returns (a * b) % modulus. Works even if a * b overflows.
    Number multmod(Number a, Number b, NumberView modulus);

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

    // Generates a prime number in the range [min, max)
    Number generatePrime(NumberView min, NumberView max);

    // Generates a prime number with a given number of bits
    inline Number generatePrime(NumberView bitCount) {
        Number min = pow(2, bitCount - 1);
        return generatePrime(min, min << 1);
    }

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
