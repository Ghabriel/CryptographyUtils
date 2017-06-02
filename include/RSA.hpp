#ifndef RSA_HPP
#define RSA_HPP

#include <utility>
#include "traits.hpp"

namespace crypto {
    using RSAKey = std::pair<Number, Number>;

    class RSA {
     public:
        std::pair<RSAKey, RSAKey> generateKeyPair(std::size_t) const;
    };
}

#endif
