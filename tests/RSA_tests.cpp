#include "debug.hpp"
#include "RSA.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::RSA;

    auto alice = RSA(RSA::generateKeyPair(42));
    auto bob = RSA(RSA::generateKeyPair(42));
    XTRACE(alice.debug());
    XTRACE(bob.debug());

    Number plaintext = 1234;
    TRACE(plaintext);
    auto aliceToBob = alice.encrypt(plaintext, bob.getPublicKey());
    TRACE(aliceToBob);
    auto bobDecrypt = bob.decrypt(aliceToBob);
    TRACE(bobDecrypt);

    auto bobToAlice = bob.encrypt(plaintext, alice.getPublicKey());
    TRACE(bobToAlice);
    auto aliceDecrypt = alice.decrypt(bobToAlice);
    TRACE(aliceDecrypt);

    // auto params = RSA::genGlobalParams(42);
    // XTRACE(params);
    // auto alice = RSA(params);
    // auto bob = RSA(params);
    // auto k1 = alice.secretKey(bob.getPublicKey());
    // auto k2 = bob.secretKey(alice.getPublicKey());
    // TRACE(k1);
    // TRACE(k2);
}

// #include <cmath>
// #include <iomanip>
// #include <iostream>
// #include <vector>
// #include "RSA.hpp"

// int main(int, char**) {
//     crypto::RSA rsa;
//     auto keyPair = rsa.generateKeyPair(30);
//     std::cout << "n1 = " << keyPair.first.first << std::endl;
//     std::cout << "n2 = " << keyPair.second.first << std::endl;
//     std::cout << "e = " << keyPair.first.second << std::endl;
//     std::cout << "d = " << keyPair.second.second << std::endl;
// }
