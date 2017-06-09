#include <algorithm>
#include <iostream>
#include "traits.hpp"
#include "utils.hpp"

using crypto::Number;

int main(int, char**) {
    // crypto::Number n = 9360;
    // crypto::Number n = 49;
    crypto::Number n = 20413;
    // crypto::Number n = 20431;
    auto factors = crypto::factorize<crypto::FactorizationAlgorithm::naive>(n);
    std::sort(factors.begin(), factors.end());
    std::cout << "Factors found: " << factors.size() << std::endl;
    bool first = true;
    for (auto& factor : factors) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << factor;
        first = false;
    }
    std::cout << std::endl;
}
