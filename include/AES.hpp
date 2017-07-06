#ifndef AES_HPP
#define AES_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include "traits.hpp"

namespace crypto {
    class AES {
     public:
        using input128 = std::array<uint8_t, 16>;
        using input192 = std::array<uint8_t, 24>;
        using input256 = std::array<uint8_t, 32>;
        input128 apply(const input128& message, const input128& key) const {
            return internalApply(message, key, 10);
        }

        input192 apply(const input192& message, const input192& key) const {
            return internalApply(message, key, 12);
        }

        input256 apply(const input256& message, const input256& key) const {
            return internalApply(message, key, 14);
        }

     private:
        template<typename T>
        T internalApply(T, const T&, size_t) const;
    };
}

#include "AES.ipp"

#endif
