#include "debug.hpp"
#include "DiffieHellman.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::DiffieHellman;

    auto params = DiffieHellman::genGlobalParams(42);
    XTRACE(params);
    auto alice = DiffieHellman(params);
    auto bob = DiffieHellman(params);
    auto k1 = alice.secretKey(bob.getPublicKey());
    auto k2 = bob.secretKey(alice.getPublicKey());
    TRACE(k1);
    TRACE(k2);
}
