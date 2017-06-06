#include <array>
#include <cmath>
#include <iostream>
#include "primality/AKS.hpp"
#include "traits.hpp"
#include "utils.hpp"

using crypto::Number;

int main(int, char**) {
    // crypto::AKS tester;

    // Number n = 31;
    // std::cout << tester.test(n) << std::endl;

    // std::cout << crypto::generatePrime() << std::endl;
    for (size_t i = 0; i < 5; i++) {
        std::cout << crypto::random(0, 10) << std::endl;
    }
}
