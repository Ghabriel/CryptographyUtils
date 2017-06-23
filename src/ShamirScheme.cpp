#include <cassert>
#include "debug.hpp"
#include "xtrace.hpp"
#include "ShamirScheme.hpp"

using crypto::Number;
using PartGroup = crypto::ShamirScheme::PartGroup;

crypto::ShamirScheme::ShamirScheme(NumberView k, NumberView n, NumberView p)
 : k(k), n(n), modulus(p) {}

PartGroup crypto::ShamirScheme::split(NumberView secret) const {
    assert(secret < modulus);
    std::vector<Number> coefs;
    coefs.reserve(k);
    coefs.push_back(secret);

    coefs.push_back(42);
    // coefs.push_back(166);
    // coefs.push_back(94);
    // for (Number i = 0; i < k - 1; ++i) {
    //  coefs.push_back(random(1, p));
    // }

    PartGroup parts;
    for (Number i = 1; i <= n; ++i) {
        parts.push_back({i, apply(coefs, i)});
    }

    return parts;
}

Number crypto::ShamirScheme::reconstruct(const PartGroup& parts) const {
    intmax_t numParts = parts.size();
    if (numParts < k) {
        throw InsufficientPartsException(k, parts.size());
    }

    Number result = 0;
    for (Number j = 0; j <= k - 1; ++j) {
        auto xj = parts[j].first;
        auto yj = parts[j].second;
        Number product = 1;
        for (Number m = 0; m <= k - 1; ++m) {
            if (m != j) {
                auto xm = parts[m].first;
                // product *= static_cast<double>(xm) / (xm - xj);
                auto delta = xm - xj;
                if (delta < 0) {
                    delta += modulus;
                }
                product *= multmod(xm, multInverse(delta, modulus), modulus);
            }
        }

        result += multmod(yj, product, modulus);
    }

    if (result < 0) {
        result += modulus;
    }

    return result;
}

Number crypto::ShamirScheme::apply(const std::vector<Number>& coefs, NumberView input) const {
    Number result = 0;
    for (std::size_t i = 0; i < coefs.size(); i++) {
        result += multmod(coefs[i], pow(input, i, modulus), modulus);
        result %= modulus;
    }
    return result;
}
