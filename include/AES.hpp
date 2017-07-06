#ifndef AES_HPP
#define AES_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

namespace crypto {
    class AES {
     public:
        using input128 = std::array<uint8_t, 16>;
        using input192 = std::array<uint8_t, 24>;
        using input256 = std::array<uint8_t, 32>;
        using Key = std::array<uint8_t, 16>;
        using Word = uint32_t;
        input128 apply(const input128& message, const Key& key) const {
            return internalApply(message, key, 10);
        }

        input192 apply(const input192& message, const Key& key) const {
            return internalApply(message, key, 12);
        }

        input256 apply(const input256& message, const Key& key) const {
            return internalApply(message, key, 14);
        }

     private:
        template<typename T>
        T internalApply(T, const Key&, size_t) const;

        std::vector<Word> keyExpansion(const Key& key) const;
    };
}

#include "AES.ipp"

#endif
