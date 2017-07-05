#include "SAES.hpp"

using InputType = crypto::SAES::InputType;

std::string crypto::SAES::apply(InputType state, const InputType& key) const {

}

std::vector<HalfKey> crypto::SAES::keyExpansion(const InputType& key) const {
    std::vector<HalfKey> result;
    result.reserve(6);

    constexpr static HalfKey rcon1 = 0x80;
    constexpr static HalfKey rcon2 = 0x30;

    HalfKey w0 = (key & 0xFF00) >> 8;
    HalfKey w1 = key & 0xFF;
    // auto w2 = w0 ^ rcon1 ^ substNibbles(rotateNibbles(w1));
    // auto w3 = w2 ^ w1;
    // auto w4 = w2 ^ rcon2 ^ substNibbles(rotateNibbles(w2));
    // auto w5 = w4 ^ w3;

    result.push_back(w0);
    result.push_back(w1);
}
