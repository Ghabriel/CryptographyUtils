#include <cmath>
#include <iostream>
#include <vector>
#include "primality/AKS.hpp"
#include "traits.hpp"
#include "utils.hpp"

using Number = crypto::Number;

int main(int, char**) {
    crypto::AKS tester;

    Number n = 31;
    std::cout << tester.test(n) << std::endl;
}
