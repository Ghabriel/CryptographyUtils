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
        InputType apply(InputType message, const InputType& key) const;

        const static std::unordered_map<HalfKey, HalfKey> sbox;
        const static std::array<std::array<uint8_t, 14>, 14> multTable;

     private:
        std::vector<HalfKey> keyExpansion(const InputType& key) const;

        HalfKey rotateNibbles(const HalfKey& value) const {
            return ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);
        }

        template<typename T>
        uint8_t nibble(const T& value, size_t index) const {
            size_t numNibbles = 2 * sizeof(value);
            auto shift = 4 * (numNibbles - index - 1);
            auto mask = 0xF << shift;
            return (value & mask) >> shift;
        }

        InputType nibbleSwap(const InputType& value) const {
            InputType result = 0;
            result |= value & 0xF000;
            result |= (value & 0x000F) << 8;
            result |= value & 0x00F0;
            result |= (value & 0x0F00) >> 8;
            return result;
        }

        template<typename T>
        T substNibbles(const T& value) const {
            size_t numNibbles = 2 * sizeof(value);
            T result = 0;
            for (size_t i = 0; i < numNibbles; i++) {
                auto shift = 4 * (numNibbles - 1 - i);
                auto mask = 0xF << shift;
                result |= sbox.at((value & mask) >> shift) << shift;
            }

            return result;
        }

        uint8_t product(uint8_t a, uint8_t b) const {
            if (a <= 1 || b <= 1) {
                return a * b;
            }

            return multTable[a - 2][b - 2];
        }
    };
}

#endif
