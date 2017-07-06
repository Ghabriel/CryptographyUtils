#include "SAES.hpp"

using InputType = crypto::SAES::InputType;
using HalfKey = crypto::SAES::HalfKey;

const std::unordered_map<HalfKey, HalfKey> crypto::SAES::sbox = {
    {0x0, 0x9},
    {0x1, 0x4},
    {0x2, 0xA},
    {0x3, 0xB},
    {0x4, 0xD},
    {0x5, 0x1},
    {0x6, 0x8},
    {0x7, 0x5},
    {0x8, 0x6},
    {0x9, 0x2},
    {0xA, 0x0},
    {0xB, 0x3},
    {0xC, 0xC},
    {0xD, 0xE},
    {0xE, 0xF},
    {0xF, 0x7},
};

const std::array<std::array<uint8_t, 14>, 14> crypto::SAES::multTable = {{
    {4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13},
    {6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2},
    {8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9},
    {10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6},
    {12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4},
    {14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11},
    {3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1},
    {1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14},
    {7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12},
    {5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3},
    {11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8},
    {9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7},
    {15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5},
    {13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10}
}};

InputType crypto::SAES::apply(InputType state, const InputType& key) const {
    auto w = keyExpansion(key);

    auto key0 = (w[0] << 8) | w[1];
    auto key1 = (w[2] << 8) | w[3];
    auto key2 = (w[4] << 8) | w[5];

    state ^= key0;

    InputType round1 = nibbleSwap(substNibbles(state));
    auto s00 = product(1, nibble(round1, 0)) ^ product(4, nibble(round1, 1));
    auto s10 = product(4, nibble(round1, 0)) ^ product(1, nibble(round1, 1));
    auto s01 = product(1, nibble(round1, 2)) ^ product(4, nibble(round1, 3));
    auto s11 = product(4, nibble(round1, 2)) ^ product(1, nibble(round1, 3));
    InputType s = 0;
    s |= s00 << 12;
    s |= s10 << 8;
    s |= s01 << 4;
    s |= s11;
    round1 = s ^ key1;

    return nibbleSwap(substNibbles(round1)) ^ key2;
}

std::vector<HalfKey> crypto::SAES::keyExpansion(const InputType& key) const {
    std::vector<HalfKey> result;

    constexpr static HalfKey rcon1 = 0x80;
    constexpr static HalfKey rcon2 = 0x30;

    std::array<HalfKey, 6> w;

    w[0] = (key & 0xFF00) >> 8;
    w[1] = key & 0xFF;
    w[2] = w[0] ^ rcon1 ^ substNibbles(rotateNibbles(w[1]));
    w[3] = w[2] ^ w[1];
    w[4] = w[2] ^ rcon2 ^ substNibbles(rotateNibbles(w[3]));
    w[5] = w[4] ^ w[3];

    result.insert(result.end(), w.begin(), w.end());

    return result;
}
