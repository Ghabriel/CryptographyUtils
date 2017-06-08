#ifndef DIFFIE_HELLMAN_HPP
#define DIFFIE_HELLMAN_HPP

#include <utility>
#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    class DiffieHellman {
     public:
        static std::pair<Number, Number> genGlobalParams(std::size_t);
        DiffieHellman(NumberView p, NumberView alpha);
        explicit DiffieHellman(const std::pair<Number, Number>&);

        Number getPublicKey() const {
            return publicKey;
        }

        Number secretKey(NumberView publicKey) const;

     private:
        Number p;
        Number publicKey;
        Number privateKey;
    };
}

#endif
