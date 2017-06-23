#ifndef ASMUTH_BLOOM_HPP
#define ASMUTH_BLOOM_HPP

#include <vector>
#include "traits.hpp"

namespace crypto {
    class AsmuthBloom {
     public:
        using PartGroup = std::vector<std::pair<Number, Number>>;

        AsmuthBloom(NumberView k, NumberView n);
        std::pair<Number, PartGroup> split(NumberView secret) const;
        Number reconstruct(const std::pair<Number, PartGroup>&) const;
        Number reconstruct(NumberView, const PartGroup&) const;

     private:
        Number k;
        Number n;

        std::vector<Number> generateSequence(NumberView) const;
    };
}

#endif
