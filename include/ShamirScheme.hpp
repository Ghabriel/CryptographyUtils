#ifndef SHAMIR_SCHEME_HPP
#define SHAMIR_SCHEME_HPP

#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    class InsufficientPartsException : public std::runtime_error {
     public:
        InsufficientPartsException(NumberView expected, NumberView actual)
         : std::runtime_error(
            "Insufficient number of parts (expected " +
            std::to_string(expected) + ", got " +
            std::to_string(actual) + ")") {}
    };

    class ShamirScheme {
     public:
        using PartGroup = std::vector<std::pair<Number, Number>>;

        ShamirScheme(NumberView k, NumberView n, NumberView modulus);
        PartGroup split(NumberView secret) const;
        Number reconstruct(const PartGroup&) const;

     private:
        NumberView k;
        NumberView n;
        NumberView modulus;

        Number apply(const std::vector<Number>&, NumberView) const;
    };
}

#endif
