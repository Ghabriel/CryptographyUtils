#include <algorithm>
#include <iostream>
#include "traits.hpp"
#include "utils.hpp"

using crypto::Number;

int main(int, char**) {
    crypto::Number n = 137;
    crypto::Number alpha = crypto::primitiveRoot(n);
    std::cout << "n = " << n << std::endl;
    std::cout << "Root found: " << alpha << std::endl;

    auto roots = crypto::primitiveRoots(n, alpha);
    std::sort(roots.begin(), roots.end());
    std::cout << "Other roots (" << roots.size() << "):" << std::endl;
    bool first = true;
    for (auto& root : roots) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << root;
        first = false;
    }
    std::cout << std::endl;
}
