#ifndef SHAMIR_SCHEME_HPP
#define SHAMIR_SCHEME_HPP

#include <vector>
#include "traits.hpp"

namespace crypto {
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
