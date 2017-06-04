#ifndef LUCAS_TEST_HPP
#define LUCAS_TEST_HPP

#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    class LucasTest {
     public:
        bool test(NumberView n, NumberView d, NumberView p, NumberView q) const;
    };
}

#endif
