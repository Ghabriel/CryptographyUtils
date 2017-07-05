#ifndef SAES_HPP
#define SAES_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include "traits.hpp"

namespace crypto {
    class SAES {
     public:
        using InputType = uint16_t;
        using HalfKey = uint8_t;
        std::string apply(InputType message, const InputType& key) const;

        const static std::unordered_map<HalfKey, HalfKey> sbox;

     private:
        std::vector<HalfKey> keyExpansion(const InputType& key) const;

        void addKey(InputType& state, const InputType& key) const {
            state ^= key;
        }

        HalfKey rotateNibbles(const HalfKey& value) const {
            return ((value & 0x0F) << 2) | ((value & 0xF0) >> 2);
        }

        HalfKey substNibbles(const HalfKey& value) const {
            return (sbox.at(value & 0xF0) << 4) | sbox.at(value & 0x0F);
        }
    };
}

#endif
