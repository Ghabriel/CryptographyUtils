#include <cassert>
#include <tuple>
#include "debug.hpp"
#include "RSA.hpp"

using crypto::Number;
using crypto::RSAKey;

std::pair<RSAKey, RSAKey> crypto::RSA::generateKeyPair(std::size_t keySize) {
    auto halfSize = keySize >> 1;
    auto p = generatePrime(halfSize);
    auto q = generatePrime(halfSize + (keySize & 1));
    auto n = p * q;
    auto totient = n - (p + q - 1);

    Number e;
    std::tuple<Number, Number, Number> gcdData;
    do {
        e = random(2, totient);
        gcdData = xgcd(e, totient);
    } while (std::get<2>(gcdData) != 1);

    auto& d = std::get<0>(gcdData);
    if (d < 0) {
        d += totient;
    }

    return {{n, e}, {n, d}};
}

crypto::RSA::RSA(const RSAKey& pubKey, const RSAKey& privKey)
 : modulus(pubKey.first), publicKey(pubKey.second), privateKey(privKey.second) {
    assert(pubKey.first == privKey.first);
}

crypto::RSA::RSA(const std::pair<RSAKey, RSAKey>& pair)
 : RSA(pair.first, pair.second) {}

Number crypto::RSA::apply(NumberView message, const RSAKey& key) const {
    // TODO: Padding (OAEP)
    return pow(message, key.second, key.first);
}
