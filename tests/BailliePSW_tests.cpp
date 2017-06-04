#include <gtest/gtest.h>
#include "primality/BailliePSW.hpp"

using crypto::BailliePSW;
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
    10968163441
};

TEST_P(Primes, BailliePSW) {
    BailliePSW tester;
    ASSERT_TRUE(tester.test(GetParam()));
}

TEST_P(Composites, BailliePSW) {
    BailliePSW tester;
    ASSERT_FALSE(tester.test(GetParam()));
}

INSTANTIATE_TEST_CASE_P(Primality, Primes, ::testing::ValuesIn(primes));
INSTANTIATE_TEST_CASE_P(Primality, Composites, ::testing::ValuesIn(composites));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
