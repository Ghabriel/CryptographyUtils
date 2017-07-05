#ifndef SAES_HPP
#define SAES_HPP

#include <cstdint>
#include <string>
#include "traits.hpp"

namespace crypto {
    class SAES {
     public:
        using InputType = uint16_t;
        using HalfKey = uint8_t;
        std::string apply(InputType message, const InputType& key) const;

     private:
        std::vector<HalfKey> keyExpansion(const InputType& key) const;

        void addKey(InputType& state, const InputType& key) const {
            state ^= key;
        }

        HalfKey rotateNibbles(const HalfKey& value) const {
            return ((value & 0xFF) << 4) | ((value & 0xFF00) >> 4);
        }
    };
}

#endif
