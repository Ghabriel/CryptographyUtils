#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include "debug.hpp"
#include "primality/AKS.hpp"
#include "traits.hpp"
#include "utils.hpp"

int main(int, char**) {
    using crypto::Number;

    // crypto::AKS tester;

    // Number n = 31;
    // std::cout << tester.test(n) << std::endl;

    // std::unordered_map<Number, size_t> values;
    // Number min = 0;
    // Number max = 10;
    // Number samples = 100000;

    // for (Number i = min; i < max; i++) {
    //     values[i] = 0;
    // }

    // // std::cout << crypto::generatePrime() << std::endl;
    // for (Number i = 0; i < samples; i++) {
    //     auto value = crypto::random(min, max);
    //     // auto value = std::random_device()() % 10;
    //     values[value]++;
    // }

    // for (Number i = min; i < max; i++) {
    //     double percent = 100 * static_cast<double>(values[i]) / samples;
    //     std::cout << i << ": " << values[i] << " (" << percent << "%)" << std::endl;
    // }

    // std::cout << crypto::pow(2, 262814145745ull, 67280421310721ull) << std::endl;
    // for (size_t i = 0; i < 10; i++) {
        std::cout << crypto::generatePrime() << std::endl;
    // }
}
