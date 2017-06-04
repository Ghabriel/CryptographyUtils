#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "primality/AKS.hpp"
#include "traits.hpp"
#include "utils.hpp"

using Number = crypto::Number;

int main(int, char**) {
    // crypto::AKS tester;

    // Number n = 31;
    // std::cout << tester.test(n) << std::endl;

    std::unordered_map<unsigned, unsigned> values;
    unsigned min = 1;
    unsigned max = 100;
    unsigned num_attempts = 1e5;

    for (unsigned i = min; i <= max; i++) {
        values[i] = 0;
    }

    for (unsigned i = 0; i < num_attempts; i++) {
        auto v = crypto::random(min, max + 1);
        values[v]++;
    }

    for (unsigned i = min; i <= max; i++) {
        std::cout << i << ": " << values[i]
        << " (" << (100 * static_cast<double>(values[i]) / num_attempts) << "%)" << std::endl;
    }
}
