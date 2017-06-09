#ifndef RSA_HPP
#define RSA_HPP

#include <cmath>
#include <utility>
#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    using RSAKey = std::pair<Number, Number>;

    class RSA {
     public:
        static std::pair<RSAKey, RSAKey> generateKeyPair(std::size_t);
        RSA(const RSAKey& publicKey, const RSAKey& privateKey);
        explicit RSA(const std::pair<RSAKey, RSAKey>&);

        inline RSAKey getPublicKey() const {
            return {modulus, publicKey};
        }

        inline Number encrypt(NumberView message, const RSAKey& externalPublicKey) const {
            return apply(message, externalPublicKey);
        }

        inline Number decrypt(NumberView message) const {
            return apply(message, privateKey);
        }

        inline Number sign(NumberView message) const {
            return apply(message, privateKey);
        }

        inline Number authenticate(NumberView message, const RSAKey& externalPublicKey) const {
            return apply(message, externalPublicKey);
        }

        inline std::string debug() const {
            return  "\n\tModulus: " + std::to_string(modulus) + " (size: " + std::to_string(static_cast<Number>(std::ceil(std::log2(modulus)))) + " bits)" +
                    "\n\tPublic Exponent: " + std::to_string(publicKey) +
                    "\n\tPrivate Exponent: " + std::to_string(privateKey);
        }

     private:
        Number modulus;
        Number publicKey;
        Number privateKey;

        Number apply(NumberView message, const RSAKey& key) const;

        inline Number apply(NumberView message, const Number& key) const {
            return apply(message, {modulus, key});
        }
    };
}

#endif
