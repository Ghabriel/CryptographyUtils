
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
