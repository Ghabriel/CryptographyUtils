#ifndef MILLER_RABIN_HPP
#define MILLER_RABIN_HPP

#include <vector>
#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    class MillerRabin {
     public:
        bool test(NumberView n, NumberView accuracy = 10) const;

        template<typename Iterable, typename = typename std::enable_if<
            !std::is_convertible<Iterable, std::size_t>::value
        >::type>
        bool test(NumberView n, const Iterable& bases) const;

     private:
        template<typename Iterable>
        bool internalTest(NumberView n, const Iterable& bases) const;
    };
}

#include "MillerRabin.ipp"

#endif
