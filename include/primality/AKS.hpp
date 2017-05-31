#ifndef AKS_HPP
#define AKS_HPP

#include <vector>
#include "traits.hpp"

namespace crypto {
    using Polynomial = std::vector<Number>;

    class AKS {
     public:
        bool test(NumberView);

     private:
        // Determines if n = a^b for integers a > 1 and b > 1.
        // Complexity: O(log n (log log n)²)
        bool isPerfectPower(NumberView);

        Number findR(NumberView);

        // Checks if (X + a)^n == X^n + a (mod X^r - 1, n)
        bool testANR(Number, NumberView, NumberView);

        Number degree(const Polynomial&, NumberView);
        Polynomial polyPowMod(const Polynomial&, Number, NumberView, NumberView);
        void polyMultMod(Polynomial&, const Polynomial&, const Polynomial&, NumberView, NumberView);
    };
}

#endif
