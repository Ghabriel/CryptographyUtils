#ifndef MILLER_RABIN_HPP
#define MILLER_RABIN_HPP

#include <array>
#include <vector>
#include "traits.hpp"

namespace crypto {
    class MillerRabin {
     public:
        bool test(NumberView n, NumberView accuracy = 10) const;

        template<typename Iterable, typename = typename std::enable_if<
            !std::is_convertible<Iterable, std::size_t>::value
        >::type>
        bool test(NumberView n, const Iterable& bases) const;

        template<size_t N = 7>
        constexpr static std::array<size_t, N> bestKnownBase();
        static std::vector<size_t> bestKnownBase(size_t);

     private:
        template<typename Iterable>
        bool internalTest(NumberView n, const Iterable& bases) const;
    };
}

#include "MillerRabin.ipp"

#endif
