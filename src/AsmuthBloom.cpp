#include <algorithm>
#include <vector>
#include <unordered_set>
#include "AsmuthBloom.hpp"
#include "debug.hpp"
#include "xtrace.hpp"

using crypto::Number;
using PartGroup = crypto::AsmuthBloom::PartGroup;

crypto::AsmuthBloom::AsmuthBloom(NumberView k, NumberView n) : k(k), n(n) {}

std::pair<Number, PartGroup> crypto::AsmuthBloom::split(NumberView secret) const {
    auto m = generateSequence(secret);
    Number rhs = 1;
    for (Number i = 1; i <= k; ++i) {
        rhs *= m[i];
    }

    Number alpha;
    Number lhs;
    do {
        alpha = generatePrime(1, 1 + (rhs - secret) / m[0]);
        lhs = secret + alpha * m[0];
    } while (lhs >= rhs);

    PartGroup parts;
    for (Number i = 1; i <= n; ++i) {
        parts.push_back({lhs % m[i], m[i]});
    }

    return {m[0], parts};
}

Number crypto::AsmuthBloom::reconstruct(const std::pair<Number, PartGroup>& data) const {
    return reconstruct(data.first, data.second);
}

Number crypto::AsmuthBloom::reconstruct(NumberView m0, const PartGroup& parts) const {
    intmax_t numParts = parts.size();
    if (numParts < k) {
        // throw InsufficientPartsException(k, parts.size());
        throw 42;
    }

    ChineseRemainder calculator;
    for (auto& part : parts) {
        calculator.push(part.first, part.second);
    }

    return calculator.eval() % m0;
}

std::vector<Number> crypto::AsmuthBloom::generateSequence(NumberView secret) const {
    std::vector<Number> m;
    m.reserve(n + 1);
    std::unordered_set<Number> mSet;

    auto initMinBound = secret + 1;
    auto initMaxBound = secret * 10;
    auto offset = pow(10, k);
    auto minBound = secret * offset;
    auto maxBound = (secret + 100 * n) * offset * 10;

    while (true) {
        mSet.insert(generatePrime(initMinBound, initMaxBound));

        intmax_t setSize = mSet.size();
        while (setSize < n + 1) {
            mSet.insert(generatePrime(minBound, maxBound));
            setSize = mSet.size();
        }

        m.clear();
        std::copy(mSet.begin(), mSet.end(), std::back_inserter(m));
        std::sort(m.begin(), m.end());
        XTRACE(m);

        Number lhs = 1;
        for (Number i = n - k + 2; i <= n; i++) {
            lhs *= m[i];
        }

        Number rhs = 1;
        for (Number i = 1; i <= k; i++) {
            rhs *= m[i];
        }

        mSet.clear();

        if (m[0] * lhs < rhs) {
            break;
        }
    }

    return m;
}
