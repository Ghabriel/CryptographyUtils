#include <cmath>
#include <iostream>
#include "traits.hpp"
#include "utils.hpp"

using Number = crypto::Number;

int main(int, char**) {
    for (Number i = 0; i < 10; i++) {
        for (Number j = 0; j < 10; j++) {
            auto r1 = crypto::pow(i, j);
            auto r2 = std::pow(i, j);
            std::cout << i << "^" << j << " = "
            << r1 << "\t" << r2 << "\n";
        }
    }
}
