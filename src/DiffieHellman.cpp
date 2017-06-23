#include "DiffieHellman.hpp"
#include "primality/MillerRabin.hpp"
#include "utils.hpp"

using crypto::Number;

// Based on: https://crypto.stackexchange.com/questions/820/how-does-one-calculate-a-primitive-root-for-diffie-hellman?rq=1
std::pair<Number, Number> crypto::DiffieHellman::genGlobalParams(std::size_t size) {
    MillerRabin tester;
    Number q;
    Number p;
    do {
        q = generatePrime(size - 1);
        p = 2 * q + 1;
    } while (!tester.test(p, MillerRabin::bestKnownBase<7>()));

    return {p, random(2, p - 1)};
}

crypto::DiffieHellman::DiffieHellman(NumberView p, NumberView alpha) : p(p) {
    privateKey = random(1, p);
    publicKey = pow(alpha, privateKey, p);
}

crypto::DiffieHellman::DiffieHellman(const std::pair<Number, Number>& params)
 : DiffieHellman(params.first, params.second) {}

Number crypto::DiffieHellman::secretKey(NumberView externalPublicKey) const {
    return pow(externalPublicKey, privateKey, p);
}
