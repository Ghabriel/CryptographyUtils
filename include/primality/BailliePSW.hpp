#ifndef BAILLIE_PSW_HPP
#define BAILLIE_PSW_HPP

#include <vector>
#include "primality/MillerRabin.hpp"
#include "primality/LucasTest.hpp"
#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    class BailliePSW {
     public:
        bool test(NumberView n) const;
    };
}

#endif
