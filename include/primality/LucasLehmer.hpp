#ifndef LUCAS_LEHMER_HPP
#define LUCAS_LEHMER_HPP

#include "traits.hpp"

namespace crypto {
    namespace detail {
        bool lucasLehmer(NumberView mp, NumberView p, Number s) {
            for (Number i = 0; i < p - 2; i++) {
                s = ((s * s) - 2) % mp;
            }
            return s == 0;
        }
    }

    class LucasLehmer {
     public:
        bool test(const Number& mp, const Number& p) {
            return detail::lucasLehmer(mp, p, 4);
        }
    };

    class LucasLehmerRiesel {
     public:
        bool test(const Number& mp, const Number& p, const Number& k) {
            auto s = [=]() -> Number {
                if (k == 1) {
                    if (p % 2) return 4;
                    if (p % 4 == 3) return 3;
                } else if (k == 3) {
                    auto mod = p % 4;
                    if (mod == 0 || mod == 3) return 5778;
                } else {
                    auto mod = k % 6;
                    if (mod == 1 || mod == 5) {
                        if (mp % 3 == 0) {
                            constexpr double w1 = 2 + sqrt(3);
                            constexpr double w2 = 2 - sqrt(3);
                            return round(pow(w1, k) + pow(w2, k));
                        }
                    }
                }
                // std::cout << "[TODO] Invalid parameters: k = " << k << ", p = " << p << std::endl;
                // TODO: investigate the other cases
                throw 42;
            }();

            return detail::lucasLehmer(mp, p, s);
        }
    };

    // class FastLucasLehmer {
    //  public:
    //     bool test(const Number& mp, const Number& p) {
    //         constexpr double w1 = 2 + sqrt(3);
    //         constexpr double w2 = 2 - sqrt(3);
    //         auto exponent = pow(2, p - 2);
    //         Number sum = round(pow(w1, exponent) + pow(w2, exponent));
    //         std::cout << "[FAST] " << p << " -> " << sum << std::endl;
    //         return sum % mp == 0;
    //     }
    // };
}

#endif
