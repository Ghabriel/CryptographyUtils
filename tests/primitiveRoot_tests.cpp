#include <algorithm>
#include <iostream>
#include "traits.hpp"
#include "utils.hpp"

using Number = crypto::Number;

int main(int, char**) {
    crypto::Number n = 137;
    crypto::Number alpha = 3;
    auto roots = crypto::primitiveRoots(n, alpha);
    std::sort(roots.begin(), roots.end());
    std::cout << "Roots found: " << roots.size() << " (besides " << alpha << ")" << std::endl;
    for (auto& root : roots) {
        std::cout << root << ", ";
    }
    std::cout << std::endl;
}
