#include <cassert>

namespace crypto {
    template<>
    constexpr std::array<size_t, 1> MillerRabin::bestKnownBase<1>() {
        return {9345883071009581737ull};
    }

    template<>
    constexpr std::array<size_t, 2> MillerRabin::bestKnownBase<2>() {
        return {336781006125, 9639812373923155};
    }

    template<>
    constexpr std::array<size_t, 3> MillerRabin::bestKnownBase<3>() {
        return {
            4230279247111683200,
            14694767155120705706ull,
            16641139526367750375ull
        };
    }

    template<>
    constexpr std::array<size_t, 4> MillerRabin::bestKnownBase<4>() {
        return {2, 141889084524735, 1199124725622454117,
                11096072698276303650ull};
    }

    template<>
    constexpr std::array<size_t, 5> MillerRabin::bestKnownBase<5>() {
        return {2, 4130806001517, 149795463772692060,
                186635894390467037, 3967304179347715805};
    }

    template<>
    constexpr std::array<size_t, 6> MillerRabin::bestKnownBase<6>() {
        return {2, 123635709730000, 9233062284813009, 43835965440333360,
                761179012939631437, 1263739024124850375};
    }

    template<>
    constexpr std::array<size_t, 7> MillerRabin::bestKnownBase<7>() {
        return {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    }

    inline std::vector<size_t> MillerRabin::bestKnownBase(size_t size) {
        auto convert = [](const auto& arr) {
            return std::vector<size_t>(arr.begin(), arr.end());
        };

        switch (size) {
            case 1: return convert(bestKnownBase<1>());
            case 2: return convert(bestKnownBase<2>());
            case 3: return convert(bestKnownBase<3>());
            case 4: return convert(bestKnownBase<4>());
            case 5: return convert(bestKnownBase<5>());
            case 6: return convert(bestKnownBase<6>());
            case 7: return convert(bestKnownBase<7>());
            default: assert(false);
        }
    }
}

template<typename Iterable, typename>
inline bool crypto::MillerRabin::test(NumberView n, const Iterable& bases) const {
    if (n < 3 || n % 2 == 0) {
        return (n == 2);
    }

    return internalTest(n, bases);
}

template<typename Iterable>
inline bool crypto::MillerRabin::internalTest(NumberView n, const Iterable& bases) const {
    auto d = n - 1;
    Number r = 0;
    while (d % 2 == 0) {
        ++r;
        d >>= 1;
    }

    for (const auto& base : bases) {
        if (base % n == 0) {
            continue;
        }

        auto x = pow(base, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }

        bool skip = false;
        for (Number i = 0; i < r - 1; i++) {
            x = (x * x) % n;
            if (x == 1) {
                return false;
            }

            if (x == n - 1) {
                skip = true;
                break;
            }
        }

        if (!skip) {
            return false;
        }
    }

    return true;
}
