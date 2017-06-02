#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "RSA.hpp"

int main(int, char**) {
    crypto::RSA rsa;
    auto keyPair = rsa.generateKeyPair(8);
    std::cout << "n1 = " << keyPair.first.first << std::endl;
    std::cout << "n2 = " << keyPair.second.first << std::endl;
    std::cout << "e = " << keyPair.first.second << std::endl;
    std::cout << "d = " << keyPair.second.second << std::endl;
}
