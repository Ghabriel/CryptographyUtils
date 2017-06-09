#include <gtest/gtest.h>
#include "debug.hpp"
#include "utils.hpp"

class Tests : public ::testing::Test {};

TEST_F(Tests, AllTests) {
    using crypto::gcd;
    using crypto::multInverse;
    using crypto::Number;
    using crypto::xgcd;

    using T = std::tuple<Number, Number, Number, Number, Number>;
    const std::vector<T> data = {
        T{29, 12, 5, -12, 1},
        T{12, 29, -12, 5, 1},
        T{4, 2, 0, 1, 2},
        T{182736, 9284847, -1189212, 23405, 3}
    };

    for (auto& t : data) {
        auto& a = std::get<0>(t);
        auto& b = std::get<1>(t);
        auto& x = std::get<2>(t);
        auto& y = std::get<3>(t);
        auto& z = std::get<4>(t);
        auto expected = std::make_tuple(x, y, z);
        ASSERT_EQ(
            xgcd(a, b),
            expected
        );

        ASSERT_EQ(
            gcd(a, b),
            z
        );

        if (std::get<4>(t) == 1) {
            ASSERT_EQ(multInverse(a, b), (x + b) % b);
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
