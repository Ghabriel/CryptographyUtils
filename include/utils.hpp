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

    namespace operations {
        namespace detail {
            template<typename F>
            Number pow(Number base, Number exponent, const F&);
        }

        Number gcd(NumberView a, NumberView b);

        // Fast exponentiation. Returns base^exponent.
        Number pow(Number base, Number exponent);

        // Returns base^exponent mod modulus.
        Number pow(Number base, Number exponent, Number modulus);

        inline std::vector<Number> factorize(NumberView n) {
            // TODO
            return {};
        }

        // Euler's totient function with a given list of prime factors
        Number phi(Number n, const std::vector<Number>& factors);

        // Euler's totient function
        template<TotientAlgorithm Algorithm = TotientAlgorithm::naive>
        Number phi(NumberView n);

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
}

#endif
