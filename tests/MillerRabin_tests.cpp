#include <gtest/gtest.h>
#include "primality/MillerRabin.hpp"

using crypto::MillerRabin;
using crypto::Number;

class Primes : public ::testing::TestWithParam<Number> {};
class Composites : public ::testing::TestWithParam<Number> {};

const std::vector<Number> primes = {
    2, 3, 5, 7, 11, 13, 17, 19, 23,
    29, 137, 541, 863, 1987, 4409,
    9733, 104729, 1299709, 15485863,
    2147483647
};

const std::vector<Number> composites = {
    49, 781, 1541, 1891, 2047, 44287, 90751,
    341531, 1050535501, 10968163441,
    350269456337, 55245642489451ull,
    7999252175582851, 585226005592931977
};

TEST_P(Primes, MillerRabin) {
    MillerRabin tester;
    ASSERT_TRUE(tester.test(GetParam(), 10));
    for (size_t i = 1; i <= 7; i++) {
        if (!tester.test(GetParam(), MillerRabin::bestKnownBase(i))) {
            std::cout << "[FAIL] base size = " << i << ", param = " << GetParam() << std::endl;
            ASSERT_TRUE(false);
        }
    }
}

TEST_P(Composites, MillerRabin) {
    MillerRabin tester;
    ASSERT_FALSE(tester.test(GetParam(), 10));
    for (size_t i = 1; i <= 7; i++) {
        if (tester.test(GetParam(), MillerRabin::bestKnownBase(i))) {
            std::cout << "[SOFT FAIL] i = " << i << ", param = " << GetParam() << std::endl;
        }
    }
}

INSTANTIATE_TEST_CASE_P(Primality, Primes, ::testing::ValuesIn(primes));
INSTANTIATE_TEST_CASE_P(Primality, Composites, ::testing::ValuesIn(composites));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    if (std::is_same<Number, long long>::value) {
        std::cout << "[NOTE] crypto::Number = unsigned long long (or bigger) "
                     "corrects known-base failures for actual primes" << std::endl;
    }
    return ret;
}
