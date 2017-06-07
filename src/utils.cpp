#include <cmath>
#include <fstream>
#include <limits>
#include <random>
#include <sstream>
#include "debug.hpp"
#include "primality/MillerRabin.hpp"
#include "utils.hpp"

using crypto::Number;
using crypto::NumberView;
using crypto::TotientAlgorithm;
using crypto::FactorizationAlgorithm;

namespace crypto {
    template<>
    Number random<true>(NumberView min, NumberView max) {
        // static std::random_device rng;
        // auto value = (max - min) * rng();
        // return min + value / std::random_device::max();

        // Number rng;
        auto delta = max - min;
        auto size = std::to_string(delta).size() + 1;

        // size_t size = 8 * sizeof(Number);
        auto container = std::vector<char>(size, 0);
        auto urandom = std::ifstream("/dev/urandom", std::ios::in|std::ios::binary);
        assert(urandom);
        // urandom.read(reinterpret_cast<char*>(&rng), 1);
        urandom.read(container.data(), size);
        assert(urandom);


        std::stringstream ss;
        for (auto& value : container) {
            ss << std::abs(value % 10);
        }

        auto value = stoull(ss.str()) + std::random_device()();
        // TRACE(delta);
        // TRACE(ss.str());

        // auto value = (max - min) * rng;
        // TRACE(rng);
        // TRACE(value);
        // TRACE(std::numeric_limits<Number>::max());
        // return min + value / std::numeric_limits<Number>::max();
        // ECHO("--------------");
        return (value % delta) + min;
    }
}

Number crypto::gcd(NumberView a, NumberView b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

template<typename F>
Number crypto::detail::pow(Number base, Number exponent, const F& mult) {
    Number result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = mult(result, base);
        }
        base = mult(base, base);
        exponent >>= 1;
    }
    return result;
}

Number crypto::pow(Number base, Number exponent) {
    return detail::pow(base, exponent, [](NumberView a, NumberView b) {
        return a * b;
    });
}

// Number crypto::pow(Number base, Number exponent, Number modulus) {
//     base %= modulus;
//     TRACE(modulus);
//     return detail::pow(base, exponent, [&modulus](NumberView a, NumberView b) {
//         return (a * b) % modulus;
//     });
// }

Number crypto::pow(Number base, Number exponent, Number modulus) {
    base %= modulus;
    return detail::pow(base, exponent, [&modulus](Number a, Number b) {
        return multmod(a, b, modulus);
    });
}

Number crypto::multmod(Number a, Number b, NumberView modulus) {
    // TODO: is it worth to do a %= modulus; b %= modulus;?
    auto product = a * b;
    // Uses Russian Peasant multiplication if there's an overflow
    if (a != 0 && product / a != b) {
        Number result = 0;
        while (b > 0) {
            if (b & 1) {
                result = (result + a) % modulus;
            }
            a = (a << 1) % modulus;
            b >>= 1;
        }
        return result;
    } else {
        return product % modulus;
    }
}

// Number crypto::primitiveRoot(NumberView p) {
//     while (true) {
//         auto candidate = random(0, p);
//         if (pow(candidate, (p - 1)/2, p) == p - 1) {
//             return candidate;
//         }
//     }
// }

Number crypto::primitiveRoot(NumberView p) {
    auto totient = phi<TotientAlgorithm::prime>(p);
    auto primeFactors = factorize<FactorizationAlgorithm::naive>(totient);
    for (Number m = 2; m < p; ++m) {
        bool success = true;
        for (auto& factor : primeFactors) {
            if (pow(m, totient / factor, p) == 1) {
                success = false;
                break;
            }
        }

        if (success) {
            return m;
        }
    }

    throw 1;
}

template<typename F>
std::vector<Number> crypto::detail::primitiveRoots(NumberView n, NumberView alpha, const F& threshold) {
    std::vector<Number> result;
    auto totient = phi<TotientAlgorithm::prime>(n);
    Number i = 2;
    while (i < n) {
        if (gcd(totient, i) == 1) {
            result.push_back(::crypto::pow(alpha, i, n));
        }
        ++i;
        if (threshold(result.size())) {
            break;
        }
    }
    return result;
}

std::vector<Number> crypto::primitiveRoots(NumberView p, NumberView alpha) {
    return detail::primitiveRoots(p, alpha, [](std::size_t size) {
        return false;
    });
}

std::vector<Number> crypto::primitiveRoots(NumberView p, NumberView alpha, std::size_t limit) {
    return detail::primitiveRoots(p, alpha, [&limit](std::size_t size) {
        return size >= limit;
    });
}

template<>
std::vector<Number> crypto::factorize<FactorizationAlgorithm::naive>(Number n) {
    std::vector<Number> result;
    Number upperBound = n >> 1;

    auto test = [&](NumberView i) {
        if (n % i == 0) {
            result.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
            upperBound = n >> 1;
        }
    };

    test(2);

    for (Number i = 3; i <= upperBound; i += 2) {
        test(i);
    }

    if (n > 1) {
        result.push_back(n);
    }

    return result;
}

template<>
Number crypto::phi<TotientAlgorithm::naive>(NumberView n) {
    Number viable = 0;
    for (Number i = 1; i < n; ++i) {
        if (gcd(n, i) == 1) {
            ++viable;
        }
    }
    return viable;
}

Number crypto::phi(Number n, const std::vector<Number>& factors) {
    for (const auto& factor : factors) {
        n /= factor;
        n *= (factor - 1);
    }
    return n;
}

short crypto::jacobiSymbol(Number a, Number n) {
    short result = 1;
    while (a != 0) {
        while (a % 2 == 0) {
            a >>= 1;
            auto mod = n % 8;
            if (mod == 3 || mod == 5) {
                result = -result;
            }
        }
        std::swap(a, n);
        if (a % 4 == 3 && n % 4 == 3) {
            result = -result;
        }
        a %= n;
    }

    if (n == 1) {
        return result;
    }
    return 0;
}

bool crypto::isPerfectSquare(NumberView n) {
    Number prev = 0;
    Number x = n;
    while (std::abs(x - prev) > 5) {
        prev = std::move(x);
        x = (prev * prev + n) / (2 * prev);
    }
    return x * x == n;
}

Number crypto::generatePrime() {
    auto max = std::numeric_limits<Number>::max() / 10;
    auto min = 0;

    auto value = random(min, max);
    if (value % 2 == 0) {
        ++value;
    }

    MillerRabin tester;
    Number attempts = 1;
    while (!tester.test(value, MillerRabin::bestKnownBase<7>())) {
    // while (!tester.test(value, std::vector<Number>{2})) {
        value = random(min, max);
        while (value % 2 == 0 || value % 3 == 0 || value % 5 == 0) {
            ++value;
        }
        attempts++;
    }

    TRACE(attempts);
    return value;
}
