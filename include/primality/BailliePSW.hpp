#ifndef BAILLIE_PSW_HPP
#define BAILLIE_PSW_HPP

#include <vector>
#include "traits.hpp"

namespace crypto {
    class BailliePSW {
     public:
        bool test(NumberView n) const;
    };
}

#endif
