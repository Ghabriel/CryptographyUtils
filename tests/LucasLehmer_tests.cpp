#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "primality/LucasLehmer.hpp"
#include "traits.hpp"
#include "utils.hpp"

using Number = crypto::Number;

int main(int, char**) {
    std::vector<Number> primes = {
        3, 5, 7, 11, 13, 17, 19, 23,
        29, 31, 37, 41, 43, 47, 53, 59
    };

    crypto::LucasLehmer ll;
    crypto::LucasLehmerRiesel llr;

    using crypto::operations::pow;

    for (Number i = 0; i < 10; i++) {
        Number p = primes[i];
        Number mp = pow(2, p) - 1;
        std::cout << std::setw(10) << mp << ": "
        << (ll.test(mp, p) ? "yes" : "no") << "\t"
        << (llr.test(mp, p, 1) ? "yes" : "no") << "\n";
    }

    for (Number k = 2; k < 5; k++) {
        std::cout << "k = " << k << ":\n";
        for (Number i = 0; i < 10; i++) {
            Number p = primes[i];
            Number mp = k * pow(2, p) - 1;
            std::cout << std::setw(10) << mp << ": ";
            try {
                std::cout << (llr.test(mp, p, k) ? "yes" : "no") << "\n";
            } catch (int e) {
                std::cout << "fail\n";
            }
        }
    }
}
