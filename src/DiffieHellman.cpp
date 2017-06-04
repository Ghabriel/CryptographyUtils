#include "DiffieHellman.hpp"

using Number = crypto::Number;

std::pair<Number, Number> crypto::DiffieHellman::genGlobalParams(std::size_t size) {
    // Number p = random(0, (Number(2) << size) - 1);
    Number p = 137; // TODO
    auto alpha = primitiveRoot(p);
    return {p, alpha};
}

crypto::DiffieHellman::DiffieHellman(NumberView p, NumberView alpha)
 : p(p), alpha(alpha) {
    privateKey = random(1, p);
    publicKey = pow(alpha, privateKey, p);
}

crypto::DiffieHellman::DiffieHellman(const std::pair<Number, Number>& params)
 : DiffieHellman(params.first, params.second) {}

Number crypto::DiffieHellman::secretKey(NumberView externalPublicKey) const {
    return pow(externalPublicKey, privateKey, p);
}
